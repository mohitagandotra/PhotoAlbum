#include "networkfetcher.h"
#include "networkfetcherprivate.h"
#include "datasource.h"

#include <QLoggingCategory>



namespace  {
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
        onFetchingDone();

    m_pimpl->fetch(sources);
}

void NetworkFetcher::cancel()
{
    qCDebug(logInfo) << "Cancelling fetching";
    m_pimpl->cancel();
}

void NetworkFetcher::onFetchingDone()
{
    qCDebug(logInfo) << "Fetching done";
    setState(AbstractDatafetcher::FetchState::Finished);
}

}
