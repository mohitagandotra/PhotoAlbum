#include "user.h"

namespace SUData {
User_C::User_C(const SUCore::EntityDataBank_C &dataBank, unsigned long id, QString name, QString userName, QString email, QObject* parent) :
    Entity_C(dataBank, parent),
    m_id(id),
    m_name(name),
    m_userName(userName),
    m_email(email)
{

}

bool User_C::isValid() const
{
    return m_id != 0;
}
}
