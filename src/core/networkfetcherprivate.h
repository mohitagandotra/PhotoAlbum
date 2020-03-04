#pragma once

#include <QObject>
#include <QHash>
#include <QReadWriteLock>

#include <memory>
#include <vector>


class QNetworkAccessManager;
class QNetworkReply;

namespace SUCore {
class DataSource_I;
class NetworkFetcher;
class NetworkFetcherPrivate: public QObject
{
    Q_OBJECT

public:
    NetworkFetcherPrivate(NetworkFetcher* fetcher, QObject *parent = nullptr);
    ~NetworkFetcherPrivate();

    void fetch(const std::vector<DataSource_I*>& sources);
    void cancel();

signals:
    void downloadDone();

private:
    Q_INVOKABLE void init();
    Q_INVOKABLE void addClient(DataSource_I *src);
    Q_INVOKABLE void clearClients();
    void onFetchFinished();
    void onFetcError();

    DataSource_I* client(QNetworkReply* reply) const;
    void removeReply(QNetworkReply* reply);

private:
    NetworkFetcher *m_fetcher;
    std::unique_ptr<QThread> m_networkThread;
    std::unique_ptr<QNetworkAccessManager> m_networkManager;
    mutable QReadWriteLock m_dataLock;
    QHash<QNetworkReply*, DataSource_I*> m_requests;
};
}
