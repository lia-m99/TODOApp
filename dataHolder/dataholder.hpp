#ifndef DATAHOLDER_HPP
#define DATAHOLDER_HPP

#include <QDate>
#include <QRegularExpression>

#include "task.hpp"

namespace TODO {

class DataHolder : public QObject
{
    Q_OBJECT

public:
    DataHolder();

public:
    void addTask(const Task& task);
    void editTask(int index, const Task& editedTask);
    void removeAt(int index);

public:
    int dataSize() const;
    Task* task(int index);
    QList<Task>& matchingTasks();

public:
    void setFilterAll(Qt::CheckState all);
    void setFilterCompleted(Qt::CheckState completed);
    void setFilterStartDate(QDate start);
    void setFilterEndDate(QDate end);
    void setFilterRegex(const QRegularExpression &filter);
    void setFilterStateChanged(bool changed);

    void filterMatchingTasks();

public:
    bool hasMatchInName(const QString& name) const;
    bool hasMatchInDescription(const QString& description) const;
    bool hasMatchInDates(const QDate& date) const;
    bool hasMatchInState(bool state) const;

    bool isFilterStateChanged() const;
    bool isFilterRegexSet() const;
    bool areDatesValid() const;

public:
    void appendMatchingTask(int i);

signals:
    void dataChanged();

public:
    ~DataHolder();

private:
    // Task Data
    QList<Task> m_tasks;

    // Filters
    QRegularExpression m_filterRegex;
    QDate m_startDate;
    QDate m_endDate;
    Qt::CheckState m_completed;
    Qt::CheckState m_all;

    // Mapping and Matching Tasks
    QMap<int, int> m_filteredToOriginalIndexMap;
    QList<Task> m_matchingTasks;

    // Filter State
    bool m_filterStateChanged;

};

} // namespace TODO

#endif // DATAHOLDER_HPP
