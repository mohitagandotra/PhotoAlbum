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

void NetworkFetcherPrivate::fetch(DataSource_I *src)
{
    QMetaObject::invokeMethod(this, "addClient", Q_ARG(DataSource_I*, src));
}

void NetworkFetcherPrivate::cancel()
{
    for (auto itr = m_requests.begin(); itr != m_requests.end(); ++itr)
        itr.key()->abort();
    m_requests.clear();
}

void NetworkFetcherPrivate::init()
{
    // Create the network manager on network thread.
    m_networkManager = std::make_unique<QNetworkAccessManager>(nullptr);
    // Use the m_networkThread (Object created in main thread) so that the lamda is called on the main thread. See Thread affinity.
    connect(this, &NetworkFetcherPrivate::downloadDone, m_networkThread.get(),
            [this] (DataSource_I *src) {
        m_fetcher->onFetchingDone(src);
    });
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

void NetworkFetcherPrivate::onFetchFinished()
{
    auto reply = static_cast<QNetworkReply*>(sender());
    if (!m_requests[reply]) {
        qCDebug(logError) << "Error. No client for network reply";
        return;
    }
    DataSource_I *src = m_requests[reply];
    src->parse(reply->readAll());
    emit downloadDone(m_requests[reply]);
    m_requests.remove(reply);
    reply->deleteLater();
}

void NetworkFetcherPrivate::onFetcError()
{
    auto reply = static_cast<QNetworkReply*>(sender());
    m_requests.remove(reply);
    qCDebug(logError) << "Fetch error: " << reply->errorString();
    reply->deleteLater();
}

}
