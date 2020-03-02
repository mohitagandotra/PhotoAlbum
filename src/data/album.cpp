#include "album.h"
#include "photo.h"
#include "data/entitydatapool.h"
#include "core/entitydatabank.h"

using namespace SUCore;

namespace SUData {
Album_C::Album_C(const SUCore::EntityDataBank_C& dataBank, unsigned long id, unsigned long userId, const QString &title, QObject *parent) :
    Entity_C(dataBank, parent),
    m_id(id),
    m_userId(userId),
    m_title(title)
{

}


bool Album_C::isValid() const
{
    return m_id != 0 && m_userId != 0;
}

QUrl Album_C::albumThumbnail() const
{
    if (m_thumbnail.isEmpty()) {
        EntityDataPool_C* photosPool = m_dataBank.entityDataPool(EntityDataBank_C::EntityType::Photos);
        photosPool->forEachEntity([this](const Entity_C *e) {
            auto p = static_cast<const Photo_C*>(e);
            if (p->albumId() == m_id) {
                m_thumbnail = p->thumbnailUrl();
                return false;
            }
            return true;
        });
    }
    return m_thumbnail;
}
}
