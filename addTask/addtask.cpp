#include <QMessageBox>

#include "addtask.hpp"
#include "task.hpp"
#include "ui_addtask.h"

namespace {

const char* const INVALID_ARGUMENTS_TITLE = "Invalid Arguments";
const char* const INVALID_ARGUMENTS_MESSAGE = "All the fields are required!";
const char* const FIELD_LINE_EDIT_NAME = "lineEditName";
const char* const FIELD_TEXT_EDIT_DESCRIPTION = "textEditDescription";
const char* const FIELD_DATE_EDIT_DUE_DATE = "dateEditDueDate";
const char* const FIELD_CHECKBOX_COMPLITED = "checkBoxCompleted";

} //namespace

namespace TODO {

AddTask::AddTask(QWidget *parent, Mode mode) :
    QDialog(parent),
    ui(new Ui::AddTask),
    mode(mode) {
        connect(this, &AddTask::accepted, this, &AddTask::on_accepted);
        ui->setupUi(this);
        if(mode == Mode::Edit) {
            ui->checkBoxCompleted->setVisible(false);
            ui->labelCompleted->setVisible(false);
        }
}

void AddTask::setTaskFields(const Task& task) {
        QLineEdit* nameLineEdit = findChild<QLineEdit*>(FIELD_LINE_EDIT_NAME);
        QTextEdit* descriptionTextEdit = findChild<QTextEdit*>(FIELD_TEXT_EDIT_DESCRIPTION);
        QDateEdit* dateEdit = findChild<QDateEdit*>(FIELD_DATE_EDIT_DUE_DATE);
        QCheckBox* completedCheckBox = findChild<QCheckBox*>(FIELD_CHECKBOX_COMPLITED);

        if (nameLineEdit && descriptionTextEdit && dateEdit && completedCheckBox) {
            nameLineEdit->setText(task.m_name);
            descriptionTextEdit->setPlainText(task.m_description);
            dateEdit->setDate(task.m_date);
            completedCheckBox->setChecked(task.m_completed);
        }
}

void AddTask::on_accepted() {
    switch(mode){
        case Mode::Add:{
            QString name = ui->lineEditName->text();
            QString description = ui->textEditDescription->toPlainText();
            QDate date = ui->dateEditDueDate->date();
            bool completed = ui->checkBoxCompleted->isChecked();
            if(name.isEmpty() || description.isEmpty()){
                QMessageBox::information(this, INVALID_ARGUMENTS_TITLE, INVALID_ARGUMENTS_MESSAGE);
                return;
            }
            Task newTask = { name, description, date, completed };

            emit taskAdded(newTask);
            break;
        }
        case Mode::Edit: {
            Task editedTask;
            editedTask.m_name = ui->lineEditName->text();
            editedTask.m_description = ui->textEditDescription->toPlainText();
            editedTask.m_date = ui->dateEditDueDate->date();
            editedTask.m_completed = ui->checkBoxCompleted->isChecked();
            emit taskEdited(editedTask);
            break;
        }
        default:
            qWarning() << "Unhandled Mode" << static_cast<int>(mode);
    }
    this->close();
}

AddTask::~AddTask() {
    delete ui;
}

} // namespace TODO
