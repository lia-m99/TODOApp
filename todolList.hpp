#ifndef TODOLIST_HPP
#define TODOLIST_HPP

#include <QMainWindow>

#include "task.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class TODOList; }
QT_END_NAMESPACE

namespace TODO {

class DataHolder;
class TaskModel;

class TODOList : public QMainWindow
{
    Q_OBJECT

public:
    TODOList(QWidget *parent = nullptr);
    ~TODOList();

public:
    void setUiConnections();

private slots:
    void on_addButtonClicked();
    void on_deleteButtonClicked();
    void on_editButtonClicked();
    void on_listViewDoubleClicked(const QModelIndex &index);

    void on_taskAdded(const Task&);
    void on_taskEdited(const Task& editedTask);

    void on_textEditFilterTextChanged();
    void on_dateEditStartDateChanged(const QDate &date);
    void on_dateEditEndDateChanged(const QDate &date);
    void on_checkBoxCompletedStateChanged(int arg1);
    void on_checkBoxAllStateChanged(int state);

    void on_filterDropButtonClicked();

    void on_helpButtonClicked();
    void on_testListButtonClicked();

private:
    Ui::TODOList *ui;
    std::shared_ptr<DataHolder> m_data;

};

} // namespace TODO

#endif // TODOLIST_HPP
