#ifndef TYPES_HPP
#define TYPES_HPP

#include <QModelIndex>

namespace TODO {

enum TaskRoles {
    DisplayRole = Qt::DisplayRole,
    DueDateRole = Qt::UserRole,
    DescriptionRole = Qt::UserRole + 1,
    CompletedRole = Qt::UserRole + 2
};

enum class Mode {
    Add,
    Edit
};

} // namespace TODO

#endif // TYPES_HPP
