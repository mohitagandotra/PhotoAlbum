#pragma once

#include "datasource.h"

#include <QUrl>

class QJsonObject;

namespace SUCore {
class JsonPhotosParser_C : public DataSource_I
{
public:
    JsonPhotosParser_C(const EntityDataBank_C &dataBank);
    ~JsonPhotosParser_C() override = default;

public:
    const QUrl& source() const override { return m_url; }
    bool parse(const QByteArray &rawdata) override;

private:
    void addPhoto(const QJsonObject& obj);

private:
    const QUrl m_url;
};
}
