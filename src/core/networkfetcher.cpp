#include "networkfetcher.h"
#include "networkfetcherprivate.h"
#include "datasource.h"

#include <QLoggingCategory>



namespace  {
Q_LOGGING_CATEGORY(logError, "SUCore.NetworkFetcher", QtCriticalMsg)
Q_LOGGING_CATEGORY(logInfo, "SUCore.NetworkFetcher", QtInfoMsg)
}

namespace SUCore {

NetworkFetcher::NetworkFetcher(QObject *parent) :
    AbstractDatafetcher(parent),
    m_pimpl(new NetworkFetcherPrivate(this))
{
}

NetworkFetcher::~NetworkFetcher()
{
}

void NetworkFetcher::doFetch(const std::vector<DataSource_I *> &sources)
{
    if (!sources.size())
        setState(AbstractDatafetcher::FetchState::Finished);

    for (auto client : sources) {
        if (!m_activeSources.count(client)) {
            m_activeSources.insert(client);
            m_pimpl->fetch(client);
        }
    }
}

void NetworkFetcher::cancel()
{
    m_pimpl->cancel();
    m_activeSources.clear();
}

void NetworkFetcher::onFetchingDone(DataSource_I *src)
{
    if (src) {
        qCDebug(logInfo) << "Fetching done for: " << src->source() << "Pending count: " << m_activeSources.size();
        m_activeSources.erase(src);
        if (!m_activeSources.size()) {
            setState(AbstractDatafetcher::FetchState::Finished);
        }
    } else {
        qCDebug(logError) << "Fetching done for invalid source";
    }
}

}
