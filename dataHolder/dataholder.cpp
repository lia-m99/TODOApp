#include "datahelper.hpp"
#include "dataholder.hpp"

#include <QModelIndex>

namespace {

const char* const ACTUAL_LIST_FILE_PATH = "list.csv";

} // namespace

namespace TODO {

DataHolder::DataHolder()
    : QObject() {
    m_completed = Qt::Unchecked;
    m_all = Qt::Checked;
    m_filterStateChanged = true;
    std::vector<Task> tasks = DataHelper::readTasksFromResource(ACTUAL_LIST_FILE_PATH);
    for(const Task& task : tasks) {
        m_tasks.append(task);
    }
}

void DataHolder::addTask(const Task &task) {
    m_tasks.append(task);
    setFilterStateChanged(true);
    emit dataChanged();
}

void DataHolder::editTask(int index, const Task& editedTask) {
    if (m_filteredToOriginalIndexMap[index] >= 0 && m_filteredToOriginalIndexMap[index] < m_tasks.size()) {
        m_tasks[m_filteredToOriginalIndexMap[index]] = editedTask;
    }
    setFilterStateChanged(true);
    emit dataChanged();
}

void DataHolder::removeAt(int index) {
    if (m_filteredToOriginalIndexMap[index] < 0 || m_filteredToOriginalIndexMap[index] >= m_tasks.size())
        return;

    m_tasks.removeAt(m_filteredToOriginalIndexMap[index]);
    setFilterStateChanged(true);

    emit dataChanged();
}

int DataHolder::dataSize() const {
    return m_tasks.size();
}

Task* DataHolder::task(int index) {
    if (m_filteredToOriginalIndexMap[index] >= 0 && m_filteredToOriginalIndexMap[index] < m_tasks.size()) {
        return &m_tasks[m_filteredToOriginalIndexMap[index]];
    }
    return nullptr;
}

QList<Task>& DataHolder::matchingTasks() {
    return m_matchingTasks;
}

void DataHolder::setFilterAll(Qt::CheckState all) {
    m_all = all;
    m_filterStateChanged = true;

    emit dataChanged();
}

void DataHolder::setFilterCompleted(Qt::CheckState completed) {
    m_completed = completed;
    m_filterStateChanged = true;

    emit dataChanged();
}

void DataHolder::setFilterStartDate(QDate start) {
    m_startDate = start;
    m_filterStateChanged = true;

    emit dataChanged();
}

void DataHolder::setFilterEndDate(QDate end) {
    m_endDate = end;
    m_filterStateChanged = true;

    emit dataChanged();
}

void DataHolder::setFilterRegex(const QRegularExpression& regex) {
    m_filterRegex = regex;
    m_filterStateChanged = true;

    emit dataChanged();
}

void DataHolder::setFilterStateChanged(bool changed) {
    m_filterStateChanged = changed;
    emit dataChanged();
}

void DataHolder::filterMatchingTasks() {
    if (!isFilterStateChanged()) {
        return;
    }

    m_matchingTasks.clear();
    m_filteredToOriginalIndexMap.clear();

    for (int i = 0; i < m_tasks.size(); ++i) {
        bool nameMatch = hasMatchInName(m_tasks[i].m_name);
        bool descriptionMatch = hasMatchInDescription(m_tasks[i].m_description);
        bool dateMatch = !areDatesValid() || hasMatchInDates(m_tasks[i].m_date);
        bool completedMatch = hasMatchInState(m_tasks[i].m_completed);

        if ((!isFilterRegexSet() || nameMatch || descriptionMatch) && dateMatch && completedMatch) {
            appendMatchingTask(i);
        }
    }
    setFilterStateChanged(false);
}

bool DataHolder::hasMatchInName(const QString& name) const {
    return !m_filterRegex.pattern().isEmpty() && m_filterRegex.match(name).hasMatch();
}

bool DataHolder::hasMatchInDescription(const QString& description) const {
    return !m_filterRegex.pattern().isEmpty() && m_filterRegex.match(description).hasMatch();
}

bool DataHolder::hasMatchInDates(const QDate& date) const {
    return areDatesValid() && date >= m_startDate && date <= m_endDate;
}

bool DataHolder::hasMatchInState(bool state) const {
    return (m_completed == Qt::Checked && state) || (m_completed == Qt::Unchecked && !state) || (m_all == Qt::Checked);
}

bool DataHolder::isFilterStateChanged() const {
    return m_filterStateChanged;
}

bool DataHolder::isFilterRegexSet() const {
    return !m_filterRegex.pattern().isEmpty();
}

bool DataHolder::areDatesValid() const {
    return m_startDate.isValid() && m_endDate.isValid();
}

void DataHolder::appendMatchingTask(int i) {
    m_matchingTasks.append(m_tasks[i]);
    m_filteredToOriginalIndexMap[m_matchingTasks.size() - 1] = i;
}

DataHolder::~DataHolder() {
    DataHelper::writeTasksToResource(m_tasks);
}

} // namespace TODO
