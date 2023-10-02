#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>

#include "addtask.hpp"
#include "customItemDelegate.hpp"
#include "datahelper.hpp"
#include "dataholder.hpp"
#include "taskModel.hpp"
#include "todolList.hpp"
#include "ui_todoList.h"

namespace {

const char* const STYLE_SHEET_FILE_PATH = ":/style_light.qss";
const char* const WRONG_SELECTION_TITLE = "Wrong Selection";
const char* const WRONG_SELECTION_MESSAGE = "Choose only one item in order to edit.";
const char* const TEXT_FILTER_PLACEHOLDER = "Search in name/description";
const char* const MESSAGEBOX_TITLE_DESCRIPTION = "Description";
const char* const MESSAGEBOX_TITLE_HELP = "Help";
const char* const HELP_MESSAGE = "1. Double Click on task to see the full description.\n\n2. Uncheck the \"All\" filter to use the \"Completed\".\n\n3. Use \"Test Example List\" button to have the list for playing around.";
const char* const TEST_LIST_FILE_PATH = ":/testList.csv";

int LISTVIEW_SPACING = 10;

} // namespace

namespace TODO {

TODOList::TODOList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TODOList)
{
    ui->setupUi(this);
    m_data = std::make_shared<DataHolder>();
    TaskModel* taskModel = new TaskModel(m_data, this); // view's ownership
    ui->listView->setModel(taskModel);

    ui->textEditFilter->setPlaceholderText(TEXT_FILTER_PLACEHOLDER);

    QFile styleFile(STYLE_SHEET_FILE_PATH);
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet);
    } else {
        qWarning() << "Couldn't open the stylesheet file:";
    }

    CustomItemDelegate *delegate = new CustomItemDelegate(); // view's ownership
    ui->listView->setItemDelegate(delegate);

    ui->listView->setSpacing(LISTVIEW_SPACING);

    setUiConnections();

    styleFile.close();
}

void TODOList::setUiConnections() {
    connect(ui->textEditFilter, &QTextEdit::textChanged, this, &TODOList::on_textEditFilterTextChanged);
    connect(ui->dateEditStart, &QDateEdit::userDateChanged, this, &TODOList::on_dateEditStartDateChanged);
    connect(ui->dateEditEnd, &QDateEdit::userDateChanged, this, &TODOList::on_dateEditEndDateChanged);
    connect(ui->checkBoxAll, &QCheckBox::stateChanged, this, &TODOList::on_checkBoxAllStateChanged);
    connect(ui->checkBoxCompleted, &QCheckBox::stateChanged, this, &TODOList::on_checkBoxCompletedStateChanged);
    connect(ui->addButton, &QPushButton::clicked, this, &TODOList::on_addButtonClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &TODOList::on_editButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &TODOList::on_deleteButtonClicked);
    connect(ui->listView, &QListView::doubleClicked, this, &TODOList::on_listViewDoubleClicked);
    connect(ui->filterDropButton, &QPushButton::clicked, this, &TODOList::on_filterDropButtonClicked);
    connect(ui->helpButton, &QPushButton::clicked, this, &TODOList::on_helpButtonClicked);
    connect(ui->testListButton, &QPushButton::clicked, this, &TODOList::on_testListButtonClicked);
}

void TODOList::on_addButtonClicked() {
    AddTask taskAddingWindow(this);

    connect(&taskAddingWindow, &AddTask::taskAdded, this, &TODOList::on_taskAdded);

    taskAddingWindow.exec();
}

void TODOList::on_deleteButtonClicked() {
    auto selectionModel = ui->listView->selectionModel();
    if(!selectionModel) return;
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    QList<int> rowsToRemove;

    for (const QModelIndex &index : selectedIndexes) {
        if (index.isValid()) {
            rowsToRemove.append(index.row());
        }
    }
    std::sort(rowsToRemove.begin(), rowsToRemove.end(), std::greater<int>());

    for (int i : rowsToRemove) {
        m_data->removeAt(i);
    }

    ui->listView->update();
    ui->listView->selectionModel()->clearSelection();
}

void TODOList::on_editButtonClicked() {
    auto selectionModel = ui->listView->selectionModel();
    if(!selectionModel) return;
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        if(selectedIndexes.size() > 1) {
            QMessageBox::information(this, WRONG_SELECTION_TITLE, WRONG_SELECTION_MESSAGE);
            return;
        }
        int index = selectedIndexes.first().row();
        Task selectedTask = *m_data->task(index);

        AddTask taskEditingWindow(this, Mode::Edit);
        taskEditingWindow.setTaskFields(selectedTask);

        connect(&taskEditingWindow, &AddTask::taskEdited, this, &TODOList::on_taskEdited);

        taskEditingWindow.exec();
    }
}

void TODOList::on_listViewDoubleClicked(const QModelIndex &index) {
    QMessageBox::information(this, MESSAGEBOX_TITLE_DESCRIPTION, m_data->task(index.row())->m_description);
}

void TODOList::on_taskAdded(const Task &newTask) {
    m_data->addTask(newTask);
}

void TODOList::on_taskEdited(const Task& editedTask) {
    QModelIndexList selectedIndexes = ui->listView->selectionModel()->selectedIndexes();

    if (!selectedIndexes.isEmpty()) {
        int index = selectedIndexes.first().row();

        m_data->editTask(index, editedTask);
        ui->listView->update();
    }
    ui->listView->selectionModel()->clearSelection();
}

void TODOList::on_textEditFilterTextChanged() {
    QString filterText = ui->textEditFilter->toPlainText();
    QRegularExpression filterRegex(filterText, QRegularExpression::CaseInsensitiveOption);
    m_data->setFilterRegex(filterRegex);
}

void TODOList::on_dateEditStartDateChanged(const QDate &date) {
    m_data->setFilterStartDate(date);
}

void TODOList::on_dateEditEndDateChanged(const QDate &date) {
    m_data->setFilterEndDate(date);
}

void TODOList::on_checkBoxCompletedStateChanged(int state) {
    m_data->setFilterCompleted(static_cast<Qt::CheckState>(state));
}

void TODOList::on_checkBoxAllStateChanged(int state) {
    Qt::CheckState st = static_cast<Qt::CheckState>(state);
    if(st == Qt::Unchecked) {
        ui->checkBoxCompleted->setEnabled(true);
    } else {
        ui->checkBoxCompleted->setEnabled(false);
    }
    m_data->setFilterAll(st);
}

void TODOList::on_filterDropButtonClicked() {
    m_data->setFilterCompleted(Qt::Unchecked);
    m_data->setFilterAll(Qt::Checked);
    m_data->setFilterStartDate(QDate());
    m_data->setFilterEndDate(QDate());
    m_data->setFilterRegex(QRegularExpression());
    ui->textEditFilter->clear();
    ui->dateEditStart->setDate(QDate());
    ui->dateEditEnd->setDate(QDate::currentDate());
    ui->checkBoxCompleted->setCheckState(Qt::Unchecked);
    ui->checkBoxAll->setCheckState(Qt::Checked);
    ui->listView->update();
}

void TODOList::on_helpButtonClicked() {
    QMessageBox::information(this, MESSAGEBOX_TITLE_HELP, HELP_MESSAGE);
}

void TODOList::on_testListButtonClicked() {
    std::vector<Task> tasks = DataHelper::readTasksFromResource(TEST_LIST_FILE_PATH);
    for(const Task& task : tasks) {
        m_data->addTask(task);
    }
}

TODOList::~TODOList() {
    delete ui;
}

} // namespace TODO
