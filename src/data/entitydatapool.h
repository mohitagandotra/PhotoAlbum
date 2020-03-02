#pragma once

#include "data/entity.h"

#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>

namespace SUData {
class Entity_C;
class EntityDataPool_C
{
public:
    EntityDataPool_C() = default;
    ~EntityDataPool_C() = default;

    void addEntity(std::unique_ptr<Entity_C> entity);
    Entity_C* entityAtIndex(size_t index) const;
    size_t count() const { return m_entities.size(); }

    void forEachEntity(std::function<bool(const Entity_C*)> callback) const;

private:
   std::vector<std::unique_ptr<Entity_C>> m_entities;
   std::unordered_map<unsigned long, Entity_C*> m_cache;
};
}
