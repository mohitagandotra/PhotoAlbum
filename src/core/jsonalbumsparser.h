#pragma once

#include "datasource.h"

#include <QUrl>

class QJsonObject;

namespace SUCore {
class JsonAlbumsParser_C : public DataSource_I
{
public:
    JsonAlbumsParser_C(SUData::EntityDataPool_C& dataPool);
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
