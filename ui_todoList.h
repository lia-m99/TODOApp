/********************************************************************************
** Form generated from reading UI file 'todoList.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODOLIST_H
#define UI_TODOLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TODOList
{
public:
    QWidget *centralwidget;
    QListView *listView;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QTextEdit *textEditFilter;
    QVBoxLayout *verticalLayout_3;
    QDateEdit *dateEditStart;
    QDateEdit *dateEditEnd;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *checkBoxCompleted;
    QCheckBox *checkBoxAll;
    QPushButton *filterDropButton;
    QPushButton *helpButton;
    QPushButton *testListButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TODOList)
    {
        if (TODOList->objectName().isEmpty())
            TODOList->setObjectName("TODOList");
        TODOList->resize(827, 600);
        centralwidget = new QWidget(TODOList);
        centralwidget->setObjectName("centralwidget");
        listView = new QListView(centralwidget);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(20, 120, 621, 401));
        listView->setSelectionMode(QAbstractItemView::MultiSelection);
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(670, 220, 80, 24));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(670, 260, 80, 24));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("edit-delete");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        deleteButton->setIcon(icon);
        deleteButton->setAutoDefault(false);
        editButton = new QPushButton(centralwidget);
        editButton->setObjectName("editButton");
        editButton->setGeometry(QRect(670, 300, 80, 24));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 30, 521, 84));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(8);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        textEditFilter = new QTextEdit(layoutWidget);
        textEditFilter->setObjectName("textEditFilter");

        horizontalLayout_3->addWidget(textEditFilter);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        dateEditStart = new QDateEdit(layoutWidget);
        dateEditStart->setObjectName("dateEditStart");
        dateEditStart->setDateTime(QDateTime(QDate(1999, 12, 30), QTime(20, 0, 0)));
        dateEditStart->setMaximumTime(QTime(21, 59, 59));
        dateEditStart->setCalendarPopup(true);

        verticalLayout_3->addWidget(dateEditStart);

        dateEditEnd = new QDateEdit(layoutWidget);
        dateEditEnd->setObjectName("dateEditEnd");

        verticalLayout_3->addWidget(dateEditEnd);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        checkBoxCompleted = new QCheckBox(layoutWidget);
        checkBoxCompleted->setObjectName("checkBoxCompleted");
        checkBoxCompleted->setEnabled(false);

        verticalLayout_4->addWidget(checkBoxCompleted);

        checkBoxAll = new QCheckBox(layoutWidget);
        checkBoxAll->setObjectName("checkBoxAll");
        checkBoxAll->setChecked(true);

        verticalLayout_4->addWidget(checkBoxAll);


        horizontalLayout_3->addLayout(verticalLayout_4);

        filterDropButton = new QPushButton(centralwidget);
        filterDropButton->setObjectName("filterDropButton");
        filterDropButton->setGeometry(QRect(550, 50, 91, 41));
        helpButton = new QPushButton(centralwidget);
        helpButton->setObjectName("helpButton");
        helpButton->setGeometry(QRect(670, 340, 80, 24));
        testListButton = new QPushButton(centralwidget);
        testListButton->setObjectName("testListButton");
        testListButton->setGeometry(QRect(20, 530, 621, 24));
        TODOList->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TODOList);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 827, 21));
        TODOList->setMenuBar(menubar);
        statusbar = new QStatusBar(TODOList);
        statusbar->setObjectName("statusbar");
        TODOList->setStatusBar(statusbar);

        retranslateUi(TODOList);

        QMetaObject::connectSlotsByName(TODOList);
    } // setupUi

    void retranslateUi(QMainWindow *TODOList)
    {
        TODOList->setWindowTitle(QCoreApplication::translate("TODOList", "TODOList", nullptr));
        addButton->setText(QCoreApplication::translate("TODOList", "Add", nullptr));
        deleteButton->setText(QCoreApplication::translate("TODOList", "Delete", nullptr));
        editButton->setText(QCoreApplication::translate("TODOList", "Edit", nullptr));
        textEditFilter->setPlaceholderText(QCoreApplication::translate("TODOList", "Search in name/description", nullptr));
        checkBoxCompleted->setText(QCoreApplication::translate("TODOList", "Completed", nullptr));
        checkBoxAll->setText(QCoreApplication::translate("TODOList", "All", nullptr));
        filterDropButton->setText(QCoreApplication::translate("TODOList", "Reset", nullptr));
        helpButton->setText(QCoreApplication::translate("TODOList", "Help", nullptr));
        testListButton->setText(QCoreApplication::translate("TODOList", "Test List Example", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TODOList: public Ui_TODOList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODOLIST_H
