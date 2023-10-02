#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <QDate>
#include <QFile>

#include "datahelper.hpp"
#include "task.hpp"


namespace TODO {

std::vector<Task> DataHelper::readTasksFromResource(const QString& path) {
    std::vector<Task> tasks;

    QFile resourceFile(path);

    if (resourceFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&resourceFile);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(',');

            if (parts.size() == 4) {
                QString name = parts[0];
                QString description = parts[1];
                QDate date = QDate::fromString(parts[2], Qt::ISODate);
                bool completed = (parts[3].toLower() == "true");

                Task task(name, description, date, completed);
                tasks.push_back(task);
            }
        }

        resourceFile.close();
    } else {
        qDebug() << "Error: Unable to open resource file for reading.";
    }

    return tasks;
}

void DataHelper::writeTasksToResource(const QList<Task>& tasks) {
    QFile resourceFile("list.csv");

    if (resourceFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&resourceFile);

        for (const Task& task : tasks) {
            QString line = QString("%1,%2,%3,%4\n")
                               .arg(task.m_name, task.m_description, task.m_date.toString(Qt::ISODate),
                                    task.m_completed ? "true" : "false");
            out << line;
        }

        resourceFile.close();
    } else {
        qDebug() << "Failed to open file for writing. Error:" << resourceFile.errorString();
    }
}

} // namespace TODO
