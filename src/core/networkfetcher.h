#pragma once

#include "abstractdatafetcher.h"

#include <unordered_set>
#include <memory>

class QUrl;

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

    void onFetchingDone(DataSource_I *src);

private:
    std::unordered_set<DataSource_I *> m_activeSources;
    std::unique_ptr<NetworkFetcherPrivate> m_pimpl;
};
}
