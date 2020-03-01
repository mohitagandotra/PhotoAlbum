#include "album.h"
namespace SUData {
Album_C::Album_C(unsigned long id, unsigned long userId, const QString &title, QObject *parent) :
    Entity_C(parent),
    m_id(id),
    m_userId(userId),
    m_title(title)
{

}


bool Album_C::isValid() const
{
    return m_id != 0 && m_userId != 0;
}
}
