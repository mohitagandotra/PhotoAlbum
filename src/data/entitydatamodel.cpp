#include "entitydatamodel.h"
#include "data/entity.h"
#include "data/user.h"
#include "data/entitydatapool.h"

namespace SUData {

EntityDataModel_C::EntityDataModel_C(const EntityDataPool_C &entityDataPool, QObject* parent)
    : QAbstractListModel(parent),
      m_entityDataPool(entityDataPool)
{

}

EntityDataModel_C::~EntityDataModel_C()
{

}

int EntityDataModel_C::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_entityDataPool.count();
}

QVariant EntityDataModel_C::data(const QModelIndex &index, int role) const
{
    auto e = entityObject(index.row());
    switch (role) {
    case static_cast<int>(DataRoles::IdRole):
        return QVariant::fromValue<unsigned long>(e->id());
    case static_cast<int>(DataRoles::ObjectRole):
        return QVariant::fromValue<Entity_C*>(e);
    }
    return QVariant();
}

QHash<int, QByteArray> EntityDataModel_C::roleNames() const
{
    return {
        {static_cast<int>(DataRoles::ObjectRole), "entityObject"},
        {static_cast<int>(DataRoles::IdRole), "entityId"}
    };
}

Entity_C *EntityDataModel_C::entityObject(int index) const
{
    if (index < 0)
        return nullptr;

    return m_entityDataPool.entityAtIndex(static_cast<size_t>(index));
}

}
