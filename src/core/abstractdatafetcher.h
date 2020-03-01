#pragma once

#include <QObject>

#include <vector>

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
        Finished
    };

signals:
    void progress(double);
    void stateChanged(FetchState);

public:
    bool isBusy() const;
    void fetch(const std::vector<DataSource_I *>& sources);
    virtual void cancel() = 0;

protected:
    virtual void doFetch(const std::vector<DataSource_I *>& sources) = 0;
    void setState(FetchState newState);

private:
    FetchState m_state = FetchState::Idle;
};

}

