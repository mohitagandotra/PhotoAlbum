#pragma once

#include "datasource.h"

#include <QUrl>

class QJsonObject;



namespace SUCore {
class JsonUserParser_C : public DataSource_I
{
public:
    JsonUserParser_C(SUData::EntityDataPool_C& dataPool);
    ~JsonUserParser_C() override = default;

public:
    const QUrl & source() const override { return m_url; }
    bool parse(const QByteArray &rawdata) override;

private:
    void addUser(const QJsonObject& obj);

private:
    const QUrl m_url;
};
}
