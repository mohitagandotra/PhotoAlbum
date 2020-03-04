#pragma once

#include <QObject>
#include <QHash>

#include <memory>

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

    void fetch(DataSource_I *src);
    void cancel();

signals:
    void downloadDone(DataSource_I *);

private:
    Q_INVOKABLE void init();
    Q_INVOKABLE void addClient(DataSource_I *src);
    Q_INVOKABLE void clearClients();
    void onFetchFinished();
    void onFetcError();

private:
    NetworkFetcher *m_fetcher;
    std::unique_ptr<QThread> m_networkThread;
    std::unique_ptr<QNetworkAccessManager> m_networkManager;
    QHash<QNetworkReply*, DataSource_I*> m_requests;
};
}
