#pragma once
#include "core/entitydatabank.h"

#include <QMetaType>

class QAbstactDataModel;

namespace SUCore {
class AbstractDatafetcher;
class EntityDataBank_C;
class PhotoAlbumManager_C : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int usersCount READ usersCount NOTIFY dataChanged)
    Q_PROPERTY(int albumsCount READ albumsCount NOTIFY dataChanged)
    Q_PROPERTY(int photosCount READ photosCount NOTIFY dataChanged)

public:
    PhotoAlbumManager_C(QObject* parent = nullptr);
    ~PhotoAlbumManager_C();

    int usersCount() const;
    int albumsCount() const;
    int photosCount() const;

    Q_INVOKABLE void filterAlbumsByUser(ulong userId, bool filterPhotos = false) const;
    Q_INVOKABLE void filterPhotosByAlbum(ulong albumId) const;

    EntityDataBank_C* entityDataBank() { return &m_dataBank; }

signals:
    void dataChanged();

private:
    int entityCount(EntityDataBank_C::EntityType type) const;

private:
    std::unique_ptr<AbstractDatafetcher> m_fetcher;
    EntityDataBank_C m_dataBank;
};
}
