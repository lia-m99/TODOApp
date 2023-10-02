#include <QDate>

#include "task.hpp"

namespace TODO {
    Task::Task() {}
    Task::Task(QString name, QString description, QDate date, bool completed):
            m_name(name), m_description(description), m_date(date), m_completed(completed) {}
};
