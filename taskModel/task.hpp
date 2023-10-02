#ifndef TASK_HPP
#define TASK_HPP

#include <QDate>
#include <QString>

namespace TODO {

struct Task {
    Task();
    Task(QString name, QString description, QDate date, bool completed);

    QString m_name;
    QString m_description;
    QDate m_date;
    bool m_completed;
};

} // namespace TODO

#endif // TASK_HPP
