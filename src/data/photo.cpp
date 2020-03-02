#include "photo.h"

namespace SUData {



Photo_C::Photo_C(const SUCore::EntityDataBank_C& dataBank, unsigned long id, unsigned long albumId, const QString &title,
                 const QUrl &imageUrl, const QUrl &thumbnailUrl, QObject *parent) :
    Entity_C(dataBank, parent),
    m_id(id),
    m_albumId(albumId),
    m_title(title),
    m_imageUrl(imageUrl),
    m_thumbnailUrl(thumbnailUrl)
{

}

bool Photo_C::isValid() const
{
    return m_id != 0 && m_albumId != 0;
}
}
