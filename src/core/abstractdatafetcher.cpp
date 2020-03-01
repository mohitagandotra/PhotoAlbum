#include "abstractdatafetcher.h"

#include "core/datasource.h"

namespace SUCore {

AbstractDatafetcher::AbstractDatafetcher(QObject *parent)
    : QObject(parent)
{

}

bool AbstractDatafetcher::isBusy() const
{
    return m_state == AbstractDatafetcher::FetchState::Fetching;
}

void AbstractDatafetcher::fetch(const std::vector<DataSource_I *>& sources)
{
    if (isBusy())
        return;
    setState(AbstractDatafetcher::FetchState::Fetching);
    doFetch(sources);
}

void AbstractDatafetcher::setState(AbstractDatafetcher::FetchState newState)
{
    if (m_state != newState) {
        m_state = newState;
        emit stateChanged(m_state);
    }
}

}
