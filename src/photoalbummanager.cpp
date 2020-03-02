#include "photoalbummanager.h"

#include "data/entitydatapool.h"
#include "data/album.h"
#include "data/photo.h"
#include "core/entitydatabank.h"
#include "core/networkfetcher.h"

#include <QSortFilterProxyModel>

using namespace std;
using namespace SUData;

namespace SUCore {
PhotoAlbumManager_C::PhotoAlbumManager_C(QObject *parent) :
    QObject(parent),
    m_fetcher(new NetworkFetcher),
    m_dataBank(m_fetcher.get())
{
    connect(&m_dataBank, &EntityDataBank_C::dataPoolReady, this, &PhotoAlbumManager_C::dataReady);
    m_dataBank.populate();
}

PhotoAlbumManager_C::~PhotoAlbumManager_C()
{
}

int PhotoAlbumManager_C::usersCount() const
{
    return entityCount(EntityDataBank_C::EntityType::Users);
}

int PhotoAlbumManager_C::albumsCount() const
{
    return entityCount(EntityDataBank_C::EntityType::Albums);
}

int PhotoAlbumManager_C::photosCount() const
{
    return entityCount(EntityDataBank_C::EntityType::Photos);
}

void PhotoAlbumManager_C::filterAlbumsByUser(ulong userId, bool filterPhotos) const
{
    EntityDataPool_C* albumsDataPool = m_dataBank.entityDataPool(EntityDataBank_C::EntityType::Albums);
    QSortFilterProxyModel* model = m_dataBank.entityProxyModel(EntityDataBank_C::EntityType::Albums);
    if (!model || ! albumsDataPool)
        return;

    QString regEx;
    auto addIdToRegEx = [&regEx](ulong id) {
        regEx += QString("|(^%1$)").arg(id);
    };

    albumsDataPool->forEachEntity([userId, &addIdToRegEx](const Entity_C* e) {
        Q_ASSERT(e);
        auto album = static_cast<const Album_C*>(e);
        if (album->userId() == userId)
            addIdToRegEx(album->id());
        return true;
    });

    if (!regEx.isEmpty()) {
        regEx.remove(0, 1);
        model->setFilterRegExp(regEx);
    }

    if (filterPhotos) {
    QVariant albumIDVar =
            model->data(model->index(0,0), static_cast<int>(EntityDataModel_C::DataRoles::IdRole));
    filterPhotosByAlbum(albumIDVar.value<ulong>());
    }
}

void PhotoAlbumManager_C::filterPhotosByAlbum(ulong albumId) const
{
    EntityDataPool_C* photosDataPool = m_dataBank.entityDataPool(EntityDataBank_C::EntityType::Photos);
    QSortFilterProxyModel* model = m_dataBank.entityProxyModel(EntityDataBank_C::EntityType::Photos);
    if (!model || ! photosDataPool)
        return;

    QString regEx;
    auto addIdToRegEx = [&regEx](ulong id) {
        regEx += QString("|(^%1$)").arg(id);
    };

    photosDataPool->forEachEntity([albumId, &addIdToRegEx](const Entity_C* e) {
        Q_ASSERT(e);
        auto photo = static_cast<const Photo_C*>(e);
        if (photo->albumId() == albumId)
            addIdToRegEx(photo->id());
        return true;
    });

    if (!regEx.isEmpty()) {
        regEx.remove(0, 1);
        model->setFilterRegExp(regEx);
    }
}

int PhotoAlbumManager_C::entityCount(EntityDataBank_C::EntityType type) const
{
    EntityDataPool_C* entityPool = m_dataBank.entityDataPool(type);
    if (entityPool)
        return entityPool->count();
    return -1;
}
}
