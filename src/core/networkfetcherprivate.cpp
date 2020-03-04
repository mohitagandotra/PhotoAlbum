#include "networkfetcherprivate.h"
#include "networkfetcher.h"
#include "datasource.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>
#include <QUrl>
#include <QLoggingCategory>

namespace  {
Q_LOGGING_CATEGORY(logError, "SUCore.NetworkFetcherPrivate", QtCriticalMsg);
}

using namespace std;

namespace SUCore {
NetworkFetcherPrivate::NetworkFetcherPrivate(NetworkFetcher *fetcher, QObject *parent): QObject(parent),
    m_fetcher(fetcher),
    m_networkThread(new QThread)
{
    m_networkThread->start();
    this->moveToThread(m_networkThread.get());
    QMetaObject::invokeMethod(this, "init");
}

NetworkFetcherPrivate::~NetworkFetcherPrivate()
{
    cancel();
    if (m_networkThread->isRunning()) {
        m_networkThread->quit();
        m_networkThread->wait();
    }
}

void NetworkFetcherPrivate::fetch(const vector<DataSource_I*>& sources)
{
    for (auto src : sources)
        QMetaObject::invokeMethod(this, "addClient", Q_ARG(DataSource_I*, src));
}

void NetworkFetcherPrivate::cancel()
{
    clearClients();
}

void NetworkFetcherPrivate::init()
{
    // Create the network manager on network thread.
    m_networkManager = std::make_unique<QNetworkAccessManager>(nullptr);
    connect(this, &NetworkFetcherPrivate::downloadDone, m_fetcher, &NetworkFetcher::onFetchingDone);
}

void NetworkFetcherPrivate::addClient(DataSource_I *src)
{
    if (!m_networkManager) {
        qCDebug(logError) << "Initialization not done";
        return;
    }

    Q_ASSERT(src);

    QNetworkReply *reply = m_networkManager->get(QNetworkRequest(src->source()));
    m_requests[reply] = src;

    QObject::connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
                     this, &NetworkFetcherPrivate::onFetcError);

    QObject::connect(reply, &QNetworkReply::finished, this, &NetworkFetcherPrivate::onFetchFinished);

    QObject::connect(reply, &QNetworkReply::downloadProgress, [](qint64 bytesReceived, qint64 bytesTotal) {
       qDebug() << QThread::currentThread() << "Recieved: "<< bytesReceived <<" - " << bytesTotal;
    });
}

void NetworkFetcherPrivate::clearClients()
{
    QWriteLocker lock(&m_dataLock);
    while(m_requests.size()) {
        QNetworkReply *reply = m_requests.begin().key();
        m_requests.remove(reply);
        reply->abort();
    }
    m_requests.clear();
}

void NetworkFetcherPrivate::onFetchFinished()
{
    auto reply = static_cast<QNetworkReply*>(sender());
    DataSource_I *src = client(reply);
    if (!src) {
        qCDebug(logError) << "Error. No client for network reply";
        return;
    }
    src->parse(reply->readAll());
    removeReply(reply);
}

void NetworkFetcherPrivate::onFetcError()
{
    auto reply = static_cast<QNetworkReply*>(sender());
    qCDebug(logError) << "Fetch error: " << reply->errorString();
    DataSource_I *src = client(reply);
    if (!src) {
        qCDebug(logError) << "Error. No client for network reply";
        return;
    }
    removeReply(reply);
}

DataSource_I *NetworkFetcherPrivate::client(QNetworkReply *reply) const
{
    QReadLocker lock(&m_dataLock);
    if (m_requests.count(reply))
        return m_requests[reply];
    return nullptr;
}

void NetworkFetcherPrivate::removeReply(QNetworkReply *reply)
{
    QWriteLocker lock(&m_dataLock);
    m_requests.remove(reply);
    reply->deleteLater();
    if (m_requests.size() == 0)
        emit downloadDone();
}

}
