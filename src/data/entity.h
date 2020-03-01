#pragma once
#include <QObject>

namespace SUData {
class Entity_C : public QObject
{
    Q_OBJECT
    Q_PROPERTY(unsigned long entityId READ id CONSTANT)
public:
    Entity_C(QObject* parent = nullptr);
    virtual ~Entity_C() = default;

public:
    virtual unsigned long id() const = 0;
    virtual bool isValid() const = 0;
};
}
