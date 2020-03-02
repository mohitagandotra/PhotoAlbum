#include "jsonuserparser.h"

#include "data/user.h"
#include "data/entitydatapool.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLoggingCategory>

#include <memory>

namespace  {
Q_LOGGING_CATEGORY(errorLog, "SUCore.JsonUserParser", QtCriticalMsg);

// Json tags
const char IdTag[] = "id";
const char NameTag[] = "name";
const char UserNameTag[] = "username";
const char EmailTag[] = "email";
}

using namespace SUData;

namespace SUCore {

JsonUserParser_C::JsonUserParser_C(const EntityDataBank_C &dataBank) :
    DataSource_I(dataBank),
    m_url("https://jsonplaceholder.typicode.com/users")
{

}

bool JsonUserParser_C::parse(const QByteArray &rawdata)
{
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(rawdata, &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qCDebug(errorLog) << "User data parsing error. " << jsonError.errorString();
        return false;
    }

    QJsonArray users = doc.array();
    for (auto itr = users.cbegin(); itr != users.cend(); ++itr)
        addUser(itr->toObject());

    return true;
}

void JsonUserParser_C::addUser(const QJsonObject &obj)
{
    std::unique_ptr<User_C> user = std::make_unique<User_C>(m_dataBank,
                                                            obj.value(IdTag).toInt(0),
                                                            obj.value(NameTag).toString(),
                                                            obj.value(UserNameTag).toString(),
                                                            obj.value(EmailTag).toString());
    if (!user->isValid()) {
        qCDebug(errorLog) << "Invalid user" << obj;
        return;
    }
    addEntity(EntityDataBank_C::EntityType::Users, std::move(user));
}

}
