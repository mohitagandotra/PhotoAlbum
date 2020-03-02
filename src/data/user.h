#pragma once
#include "entity.h"

#include <QString>

namespace SUData {
class User_C : public Entity_C
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString userName READ userName CONSTANT)
    Q_PROPERTY(QString email READ email CONSTANT)

public:
    User_C(const SUCore::EntityDataBank_C& dataBank, unsigned long id, QString name, QString userName, QString email, QObject* parent = nullptr);

    bool isValid() const override;
    unsigned long id() const override { return m_id; }
    const QString& name() const { return m_name; }
    const QString& userName() const { return m_userName; }
    const QString& email() const { return m_email; }

private:
    const unsigned long m_id = 0;
    QString m_name;
    QString m_userName;
    QString m_email;
};
}
