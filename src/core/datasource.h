#pragma once

#include <QMetaType>

class QUrl;
class QByteArray;

namespace SUData {
class Entity_C;
class EntityDataPool_C;
}

namespace SUCore {
class DataSource_I
{
public:
    DataSource_I(SUData::EntityDataPool_C& dataPool);
    virtual ~DataSource_I() = default;

public:
    virtual const QUrl& source() const = 0;
    virtual bool parse(const QByteArray& rawdata) = 0;

protected:
    void addEntity(std::unique_ptr<SUData::Entity_C> entity);

private:
    SUData::EntityDataPool_C& m_userDataPool;
};
}
Q_DECLARE_METATYPE(SUCore::DataSource_I*);
