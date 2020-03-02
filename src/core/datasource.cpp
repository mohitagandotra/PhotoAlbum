#include "datasource.h"
#include "data/entity.h"

#include "data/entitydatapool.h"

namespace SUCore {

DataSource_I::DataSource_I(const EntityDataBank_C &m_dataBank) :
    m_dataBank(m_dataBank)
{

}

void DataSource_I::addEntity(EntityDataBank_C::EntityType type, std::unique_ptr<SUData::Entity_C> entity)
{
    SUData::EntityDataPool_C* pool = m_dataBank.entityDataPool(type);
    Q_ASSERT(pool);
    pool->addEntity(std::move(entity));
}

}
