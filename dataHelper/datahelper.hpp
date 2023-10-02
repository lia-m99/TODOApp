#ifndef DATAHELPER_HPP
#define DATAHELPER_HPP

#include <string>
#include <vector>

#include <QFile>
#include <QString>

namespace TODO {

class Task;

class DataHelper {
public:
    static std::vector<Task> readTasksFromResource(const QString& path);
    static void writeTasksToResource(const QList<Task>& tasks);
};

} // namespace TODO

#endif // DATAHELPER_HPP
