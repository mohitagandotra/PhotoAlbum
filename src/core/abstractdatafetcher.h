#pragma once

#include <QObject>

#include <vector>
#include <QTimer>

namespace SUCore {
class DataSource_I;

class AbstractDatafetcher : public QObject
{
    Q_OBJECT

public:
    AbstractDatafetcher(QObject *parent = nullptr);
    ~AbstractDatafetcher() = default;

    enum class FetchState
    {
        Idle = 0,
        Fetching,
        Finished,
        TimedOut
    };

signals:
    void progress(double);
    void stateChanged(FetchState);

public:
    bool isBusy() const;
    void fetch(const std::vector<DataSource_I *>& sources, int timeoutMsecs = 0);
    virtual void cancel() = 0;

protected:
    virtual void doFetch(const std::vector<DataSource_I *>& sources) = 0;
    void setState(FetchState newState);

private:
    void setTimeOut(int timeoutMsecs);
    void onTimeout();

private:
    FetchState m_state = FetchState::Idle;
    std::unique_ptr<QTimer> m_timeoutTimer;
};

}

