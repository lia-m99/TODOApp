#include "dataholder.hpp"
#include "taskModel.hpp"
#include "types.hpp"

namespace TODO {

TaskModel::TaskModel(std::shared_ptr<DataHolder> data, QObject *parent)
    : QAbstractListModel(parent),
    m_data(data) {
    connect(m_data.get(), &DataHolder::dataChanged, this, &TaskModel::onDataChanged);    
}

int TaskModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    m_data->filterMatchingTasks();
    return m_data->matchingTasks().count();
}


QVariant TaskModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= rowCount() || index.row() < 0)
        return QVariant();

    m_data->filterMatchingTasks();

    const Task& task = m_data->matchingTasks().at(index.row());

    switch(role) {
    case TaskRoles::DisplayRole:
        return task.m_name;
    case TaskRoles::DueDateRole:
        return task.m_date;
    case TaskRoles::DescriptionRole:
        return task.m_description;
    case TaskRoles::CompletedRole:
        return task.m_completed;
    default:
        return QVariant();
    }
}

bool TaskModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() >= rowCount() || index.row() < 0)
        return false;

    Task* task = m_data->task(index.row());

    switch (role) {
    case TaskRoles::DisplayRole:
        task->m_name = value.toString();
        break;
    case TaskRoles::DueDateRole:
        task->m_date = value.toDate();
        break;
    case TaskRoles::DescriptionRole:
        task->m_description = value.toString();
        break;
    case TaskRoles::CompletedRole:
        task->m_completed = value.toBool();
        break;
    default:
        return false;
    }
    m_data->setFilterStateChanged(true);
    emit dataChanged(index, index, QVector<int>() << role);

    return true;
}

void TaskModel::onDataChanged()  {
    emit dataChanged(index(0, 0), index(rowCount() - 1, 0));
}

} // namespace TODO
