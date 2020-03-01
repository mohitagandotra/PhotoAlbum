#include "user.h"

namespace SUData {
User_C::User_C(unsigned long id, QString name, QString userName, QString email) :
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
