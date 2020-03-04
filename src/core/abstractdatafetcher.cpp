#include "abstractdatafetcher.h"

#include "core/datasource.h"

#include <QLoggingCategory>

namespace  {
Q_LOGGING_CATEGORY(logInfo, "SUCore.AbstractDatafetcher", QtInfoMsg)
Q_LOGGING_CATEGORY(logError, "SUCore.AbstractDatafetcher", QtCriticalMsg)
}

namespace SUCore {

AbstractDatafetcher::AbstractDatafetcher(QObject *parent)
    : QObject(parent)
{

}

bool AbstractDatafetcher::isBusy() const
{
    return m_state == AbstractDatafetcher::FetchState::Fetching;
}

void AbstractDatafetcher::fetch(const std::vector<DataSource_I *>& sources, int timeoutMsecs)
{
    if (isBusy())
        return;
    setTimeOut(timeoutMsecs);
    setState(AbstractDatafetcher::FetchState::Fetching);
    doFetch(sources);
}

void AbstractDatafetcher::setTimeOut(int timeoutMsecs)
{
    if (timeoutMsecs <= 0) {
        qCDebug(logInfo) << "Invalid timeout value: " << timeoutMsecs << "Timeout not set.";
        return;
    }
    m_timeoutTimer.reset(new QTimer);
    m_timeoutTimer->setInterval(timeoutMsecs);
    m_timeoutTimer->setSingleShot(true);
    connect(m_timeoutTimer.get(), &QTimer::timeout, this, &AbstractDatafetcher::onTimeout);
}

void AbstractDatafetcher::setState(AbstractDatafetcher::FetchState newState)
{
    if (m_state != newState) {
        m_state = newState;
        emit stateChanged(m_state);

        if (m_state == AbstractDatafetcher::FetchState::Fetching && m_timeoutTimer)
            m_timeoutTimer->start();

        if (m_state == AbstractDatafetcher::FetchState::Finished)
            m_timeoutTimer.reset(nullptr);
    }
}

void AbstractDatafetcher::onTimeout()
{
    qCDebug(logError) << "fetching timedout";
    if (m_state == AbstractDatafetcher::FetchState::Fetching) {
        cancel();
        setState(AbstractDatafetcher::FetchState::TimedOut);
    }
}

}
