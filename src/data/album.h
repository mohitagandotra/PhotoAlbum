#include "entity.h"

#include <QString>

namespace SUData {
class Album_C : public Entity_C
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(unsigned long userId READ userId CONSTANT)

public:
    Album_C(unsigned long id, unsigned long userId, const QString& title, QObject* parent = nullptr);

    bool isValid() const override;
    unsigned long id() const override { return m_id; }
    const QString& title() const { return m_title; }
    unsigned long userId() const { return m_userId; }

private:
    const unsigned long m_id = 0;
    const unsigned long m_userId = 0;
    QString m_title;
};
}
