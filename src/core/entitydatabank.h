#pragma once
#include "core/abstractdatafetcher.h"

#include "data/entitydatamodel.h"

#include <QObject>

#include <vector>
#include <unordered_map>
#include <memory>
#include <QQmlEngine>

class QSortFilterProxyModel;

namespace SUData {
class EntityDataPool_C;
}

using SafeModelPtr = std::unique_ptr<SUData::EntityDataModel_C>;
using SafePoolPtr = std::unique_ptr<SUData::EntityDataPool_C>;
using SafeProxyModelPtr = std::unique_ptr<QSortFilterProxyModel>;

namespace SUCore {
class DataSource_I;
using SafeSourcePtr = std::unique_ptr<DataSource_I>;

class EntityDataBank_C : public QObject
{
    Q_OBJECT

public:
    enum class EntityType {
        Users = 1,
        Albums,
        Photos
    };
    Q_ENUMS(EntityType)

    EntityDataBank_C(AbstractDatafetcher* fetcher);
    ~EntityDataBank_C();

signals:
    void dataPoolReady();
    void dataPoolTimedout();

public:
    Q_INVOKABLE void populate();
    void setQmlEngine(QQmlEngine *engine);

    SUData::EntityDataPool_C* entityDataPool(EntityType type) const;
    Q_INVOKABLE SUData::EntityDataModel_C* entityDataModel(EntityType type) const;
    Q_INVOKABLE QSortFilterProxyModel* entityProxyModel(EntityType type) const;

private:
    void reset();
    void beginFetch();
    void onFetchStateChanged(AbstractDatafetcher::FetchState state);
    void forEachEntity(std::function<void(EntityType)> callback);

private:
    static std::vector<EntityType> m_entityTypes;
    AbstractDatafetcher* m_fetcher = nullptr;
    QQmlEngine* m_qmlEngine = nullptr;
    std::vector<SafeSourcePtr> m_dataSources;
    std::unordered_map<EntityType, SafePoolPtr> m_dataPools;
    std::unordered_map<EntityType, SafeModelPtr> m_dataModels;
    std::unordered_map<EntityType, SafeProxyModelPtr> m_proxyModels;
};
}
