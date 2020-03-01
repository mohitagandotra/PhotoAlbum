#include "networkfetcher.h"
#include "networkfetcherprivate.h"
#include "datasource.h"

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
}

void NetworkFetcher::onFetchingDone(DataSource_I *src)
{
    if (src) {
        m_activeSources.erase(src);
        if (!m_activeSources.size())
            setState(AbstractDatafetcher::FetchState::Finished);
    }
}

}
