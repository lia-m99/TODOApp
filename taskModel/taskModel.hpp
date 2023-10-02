#ifndef TASKMODEL_HPP
#define TASKMODEL_HPP

#include <QAbstractListModel>

#include "types.hpp"

namespace TODO {

class DataHolder;

class TaskModel : public QAbstractListModel
{
    Q_OBJECT

public:
    TaskModel(std::shared_ptr<DataHolder> data, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = TaskRoles::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

public slots:
    void onDataChanged();

private:
    std::shared_ptr<DataHolder> m_data;
};

} // namespace TODO

#endif // TASKMODEL_HPP
