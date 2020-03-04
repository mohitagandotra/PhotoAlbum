#include "entitydatabank.h"
#include "core/abstractdatafetcher.h"
#include "core/datasource.h"
#include "data/entitydatapool.h"

#include "data/entitydatamodel.h"

// Data parsers
#include "core/jsonuserparser.h"
#include "core/jsonalbumsparser.h"
#include "core/jsonphotosparser.h"

#include <QSortFilterProxyModel>
#include <QLoggingCategory>

using namespace std;
using namespace SUData;


namespace  {
Q_LOGGING_CATEGORY(logError, "SUCore.EntityDataBank", QtCriticalMsg)
Q_LOGGING_CATEGORY(logInfo, "SUCore.EntityDataBank", QtInfoMsg)
}

namespace SUCore {
std::vector<EntityDataBank_C::EntityType> EntityDataBank_C::m_entityTypes({
                                                                          EntityType::Users,
                                                                          EntityType::Albums,
                                                                          EntityType::Photos
                                                                      });

EntityDataBank_C::EntityDataBank_C(AbstractDatafetcher *fetcher) :
    m_fetcher(fetcher)
{
    Q_ASSERT(m_fetcher);
    connect(m_fetcher, &AbstractDatafetcher::stateChanged,
            this, &EntityDataBank_C::onFetchStateChanged);
}

EntityDataBank_C::~EntityDataBank_C()
{
}

void EntityDataBank_C::populate()
{
    Q_ASSERT(m_fetcher);
    if (m_fetcher->isBusy()) {
        qCDebug(logInfo) << "Can not populate data. Fetcher busy.";
        return;
    }

    reset();
    qCDebug(logInfo) << "Populating data begin";
    // Add data pools
    forEachEntity([this](EntityType e) {
        m_dataPools.insert({e, make_unique<EntityDataPool_C>()});
    });

    // Create data sources.
    m_dataSources.push_back(make_unique<JsonUserParser_C>(*this));
    m_dataSources.push_back(make_unique<JsonAlbumsParser_C>(*this));
    m_dataSources.push_back(make_unique<JsonPhotosParser_C>(*this));

    // Begin fetch
    beginFetch();
}

void EntityDataBank_C::setQmlEngine(QQmlEngine *engine)
{
    m_qmlEngine = engine;
}

EntityDataPool_C *EntityDataBank_C::entityDataPool(EntityDataBank_C::EntityType type) const
{
    if (m_dataPools.count(type))
        return m_dataPools.at(type).get();

    return nullptr;
}

EntityDataModel_C *EntityDataBank_C::entityDataModel(EntityDataBank_C::EntityType type) const
{
    if (m_dataPools.count(type))
        return m_dataModels.at(type).get();

    return nullptr;
}

QSortFilterProxyModel *EntityDataBank_C::entityProxyModel(EntityDataBank_C::EntityType type) const
{
    if (m_dataPools.count(type))
        return m_proxyModels.at(type).get();

    return nullptr;
}

void EntityDataBank_C::reset()
{
    m_proxyModels.clear();
    m_dataModels.clear();
    m_dataPools.clear();
    m_dataSources.clear();
}

void EntityDataBank_C::beginFetch()
{
    qCDebug(logInfo) << "Fetching data";
    vector<DataSource_I*> sources;
    transform(m_dataSources.begin(), m_dataSources.end(), back_inserter(sources), [](auto &s) { return s.get();});
    m_fetcher->fetch(sources, 5000);
}

void EntityDataBank_C::onFetchStateChanged(AbstractDatafetcher::FetchState state)
{
    if (state == AbstractDatafetcher::FetchState::Finished) {
        qCDebug(logInfo) << "Fetching data finished";

        // Data population done. Remove sources.
        m_dataSources.clear();

        Q_ASSERT(m_qmlEngine);

        // Create Models
        forEachEntity([this](EntityType e) {
            // Prevent JS garbage collector to delete model objects. Explicitly define the object ownership.
            entityDataPool(e)->forEachEntity([this](const Entity_C* entity) {
                m_qmlEngine->setObjectOwnership(const_cast<Entity_C*>(entity), QQmlEngine::CppOwnership);
                return true;
            });

            m_dataModels.insert({e, make_unique<EntityDataModel_C>(*(entityDataPool(e)))});
            auto sourceModel = entityDataModel(e);
            m_qmlEngine->setObjectOwnership(sourceModel, QQmlEngine::CppOwnership);

            m_proxyModels.insert({e, make_unique<QSortFilterProxyModel>(nullptr)});
            auto proxyModel = entityProxyModel(e);
            proxyModel->setFilterRole(static_cast<int>(EntityDataModel_C::DataRoles::IdRole));
            proxyModel->setSourceModel(sourceModel);
            m_qmlEngine->setObjectOwnership(proxyModel, QQmlEngine::CppOwnership);
        });

        // Notify data ready.
        emit dataPoolReady();
    } else if (state == AbstractDatafetcher::FetchState::TimedOut) {
        qCDebug(logError) << "Data fetching timed out";
        emit dataPoolTimedout();
    }
}

void EntityDataBank_C::forEachEntity(std::function<void (EntityDataBank_C::EntityType)> callback)
{
    if (!callback)
        return;
    for(auto e : m_entityTypes) {
        callback(e);
    }
}

}
