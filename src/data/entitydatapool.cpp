#include "entitydatapool.h"

#include "data/entity.h"

#include <QLoggingCategory>

namespace  {
Q_LOGGING_CATEGORY(errorLog, "SUCore.EntityDataPool", QtCriticalMsg);
}

namespace SUData {
void EntityDataPool_C::addEntity(std::unique_ptr<Entity_C> entity)
{
    if (m_cache.count(entity->id())) {
        qCDebug(errorLog()) << "Adding duplicate users." << entity->id();
        return;
    }
    m_cache.insert({entity->id(),entity.get()});
    m_entities.push_back(std::move(entity));
}

Entity_C *EntityDataPool_C::entityAtIndex(size_t index) const
{
    if (index >= m_entities.size())
        return nullptr;
    return m_entities.at(index).get();
}

void EntityDataPool_C::forEachEntity(std::function<void (const Entity_C *)> callback) const
{
    if (!callback)
        return;
    for (const auto& e : m_entities)
        callback(e.get());
}
}
