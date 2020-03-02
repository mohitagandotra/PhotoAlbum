#pragma once

#include <QMetaType>
#include "core/entitydatabank.h"

class QUrl;
class QByteArray;

namespace SUData {
class Entity_C;
class EntityDataPool_C;
}

namespace SUCore {
class EntityDataBank_C;
class DataSource_I
{
public:
    DataSource_I(const EntityDataBank_C& m_dataBank);
    virtual ~DataSource_I() = default;

public:
    virtual const QUrl& source() const = 0;
    virtual bool parse(const QByteArray& rawdata) = 0;

protected:
    void addEntity(EntityDataBank_C::EntityType type, std::unique_ptr<SUData::Entity_C> entity);
    const EntityDataBank_C& m_dataBank;
};
}
Q_DECLARE_METATYPE(SUCore::DataSource_I*);
