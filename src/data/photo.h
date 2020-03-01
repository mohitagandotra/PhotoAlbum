#include "entity.h"

#include <QString>
#include <QUrl>

namespace SUData {
class Photo_C : public Entity_C
{
    Q_OBJECT
    Q_PROPERTY(unsigned long albumId READ albumId CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QUrl imageUrl READ imageUrl CONSTANT)
    Q_PROPERTY(QUrl thumbnailUrl READ thumbnailUrl CONSTANT)

public:
    Photo_C(unsigned long id, unsigned long albumId, const QString& title,
            const QUrl& imageUrl, const QUrl& thumbnailUrl, QObject* parent = nullptr);

    bool isValid() const override;
    unsigned long id() const override { return m_id; }
    unsigned long albumId() const { return m_albumId; }
    const QString& title() const { return m_title; }
    const QUrl& imageUrl() const { return m_imageUrl; }
    const QUrl& thumbnailUrl() const { return m_thumbnailUrl; }

private:
    const unsigned long m_id = 0;
    const unsigned long m_albumId = 0;
    QString m_title;
    QUrl m_imageUrl;
    QUrl m_thumbnailUrl;
};
}
