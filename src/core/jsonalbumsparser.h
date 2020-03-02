#pragma once

#include "datasource.h"

#include <QUrl>

class QJsonObject;

namespace SUCore {
class EntityDataBank_C;
class JsonAlbumsParser_C : public DataSource_I
{
public:
    JsonAlbumsParser_C(const EntityDataBank_C &dataBank);
    ~JsonAlbumsParser_C() override = default;

public:
    const QUrl & source() const override { return m_url; }
    bool parse(const QByteArray &rawdata) override;

private:
    void addAlbum(const QJsonObject& obj);

private:
    const QUrl m_url;
};
}
