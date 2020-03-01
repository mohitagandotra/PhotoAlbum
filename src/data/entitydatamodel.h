#pragma once
#include <QAbstractListModel>

namespace SUData {
class Entity_C;
class EntityDataPool_C;
class EntityDataModel_C : public QAbstractListModel
{
    Q_OBJECT

public:
    enum class DataRoles {
        IdRole = Qt::UserRole + 1,
        ObjectRole
    };

    EntityDataModel_C(const EntityDataPool_C &entityDataPool, QObject* parent = nullptr);
    ~EntityDataModel_C() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE Entity_C *entityObject(int index) const;

private:
    const EntityDataPool_C& m_entityDataPool;
};
}
