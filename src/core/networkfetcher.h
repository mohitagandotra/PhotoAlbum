#pragma once

#include "abstractdatafetcher.h"

#include <memory>

namespace SUCore {
class DataSource_I;
class NetworkFetcherPrivate;
class NetworkFetcher : public AbstractDatafetcher
{
public:
    NetworkFetcher(QObject* parent = nullptr);
    ~NetworkFetcher() override;

    void doFetch(const std::vector<DataSource_I *>& sources) override;
    void cancel() override;

    void onFetchingDone();

private:
    std::unique_ptr<NetworkFetcherPrivate> m_pimpl;
};
}
