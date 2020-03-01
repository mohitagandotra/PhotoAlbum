#include "datasource.h"
#include "data/entity.h"

#include "data/entitydatapool.h"

namespace SUCore {

DataSource_I::DataSource_I(SUData::EntityDataPool_C &dataPool) :
    m_userDataPool(dataPool)
{

}

void DataSource_I::addEntity(std::unique_ptr<SUData::Entity_C> entity)
{
    m_userDataPool.addEntity(std::move(entity));
}

}
