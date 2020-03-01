#include "jsonalbumsparser.h"

#include "data/album.h"
#include "data/entitydatapool.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>

#include <memory>

namespace  {
Q_LOGGING_CATEGORY(errorLog, "SUCore.JsonAlbumsParser", QtCriticalMsg);

// Json tags
const char IdTag[] = "id";
const char TitleTag[] = "title";
const char UserIdTag[] = "userId";
}

using namespace SUData;

namespace SUCore {

JsonAlbumsParser_C::JsonAlbumsParser_C(EntityDataPool_C& dataPool) :
    DataSource_I(dataPool),
    m_url("https://jsonplaceholder.typicode.com/albums")
{

}

bool JsonAlbumsParser_C::parse(const QByteArray &rawdata)
{
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(rawdata, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qCDebug(errorLog) << "Albums data parsing error. " << jsonError.errorString();
        return false;
    }

    QJsonArray albums = doc.array();
    for (auto itr = albums.cbegin(); itr != albums.cend(); ++itr)
        addAlbum(itr->toObject());

    return true;
}

void JsonAlbumsParser_C::addAlbum(const QJsonObject &obj)
{
    std::unique_ptr<Entity_C> album(new Album_C(obj.value(IdTag).toInt(0),
                                                obj.value(UserIdTag).toInt(0),
                                                obj.value(TitleTag).toString()));
    if (!album->isValid()) {
        qCDebug(errorLog) << "Invalid album" << obj;
        return;
    }
    addEntity(std::move(album));
}

}
