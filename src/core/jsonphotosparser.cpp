#include "jsonphotosparser.h"

#include "data/photo.h"
#include "data/entitydatapool.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>

#include <memory>

namespace  {
Q_LOGGING_CATEGORY(errorLog, "SUCore.JsonPhotosParser", QtCriticalMsg);

// Json tags
const char IdTag[] = "id";
const char AlbumIdTag[] = "albumId";
const char TitleTag[] = "title";
const char ImageUrlTag[] = "url";
const char ThumbnailUrlTag[] = "thumbnailUrl";
}

using namespace SUData;

namespace SUCore {

JsonPhotosParser_C::JsonPhotosParser_C(const EntityDataBank_C &dataBank) :
    DataSource_I(dataBank),
    m_url("https://jsonplaceholder.typicode.com/photos")
{

}

bool JsonPhotosParser_C::parse(const QByteArray &rawdata)
{
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(rawdata, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qCDebug(errorLog) << "Albums data parsing error. " << jsonError.errorString();
        return false;
    }

    QJsonArray albums = doc.array();
    for (auto itr = albums.cbegin(); itr != albums.cend(); ++itr)
        addPhoto(itr->toObject());

    return true;
}

void JsonPhotosParser_C::addPhoto(const QJsonObject &obj)
{
    std::unique_ptr<Entity_C> photo(new Photo_C(m_dataBank, obj.value(IdTag).toInt(0),
                                                obj.value(AlbumIdTag).toInt(0),
                                                obj.value(TitleTag).toString(),
                                                obj.value(ImageUrlTag).toString(),
                                                obj.value(ThumbnailUrlTag).toString()));
    if (!photo->isValid()) {
        qCDebug(errorLog) << "Invalid album" << obj;
        return;
    }
    addEntity(EntityDataBank_C::EntityType::Photos, std::move(photo));
}

}
