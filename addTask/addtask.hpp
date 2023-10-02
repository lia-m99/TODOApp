#ifndef ADDTASK_HPP
#define ADDTASK_HPP

#include <QDialog>

#include "types.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class AddTask; }
QT_END_NAMESPACE

namespace TODO {

class Task;

class AddTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddTask(QWidget *parent = nullptr, Mode mode = Mode::Add);
    ~AddTask();

public:
    void setTaskFields(const Task& task);

private slots:
    void on_accepted();

signals:
    void taskAdded(const Task &newTask);
    void taskEdited(const Task& editedTask);

private:
    Ui::AddTask *ui;
    Mode mode;
};

} // namespace TODO

#endif // ADDTASK_HPP
