#include <QApplication>
#include <QDate>

#include "customItemDelegate.hpp"
#include "types.hpp"

namespace TODO {

namespace sizes {
int spacing = 5;
int checkboxSize = 30;
}

CustomItemDelegate::CustomItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (option.state & QStyle::State_MouseOver) {
        QColor selectionColor(55, 94, 140);
        painter->fillRect(option.rect, selectionColor);
        painter->setPen(Qt::white);
    } else if(option.state & QStyle::State_Selected) {
        QColor selectionColor(45, 150, 130);
        painter->fillRect(option.rect, selectionColor);
        painter->setPen(Qt::white);
    } else {
        QColor softBlue(65, 114, 159);
        painter->fillRect(option.rect, softBlue);
        QColor textColor = (softBlue.lightness() < 128) ? Qt::white : QColor(0, 76, 153);
        painter->setPen(textColor);
    }

    QString taskName = index.data(TaskRoles::DisplayRole).toString();
    QDate dueDate = index.data(TaskRoles::DueDateRole).toDate();
    QString description = index.data(TaskRoles::DescriptionRole).toString();
    bool completed = index.data(TaskRoles::CompletedRole).toBool();

    QRect taskNameRect = option.rect;
    QRect dueDateRect = option.rect;
    QRect descriptionRect = option.rect;
    QRect checkboxRect = option.rect;

    QFontMetrics fontMetrics(option.font);

    int dueDateWidth = fontMetrics.boundingRect(dueDate.toString("dd.MM.yyyy")).width();
    int taskNameWidth = option.rect.width() - dueDateWidth * sizes::spacing - sizes::checkboxSize;

    taskNameRect.setRight(taskNameRect.left() + taskNameWidth + sizes::checkboxSize);
    taskNameRect.setTop(option.rect.top() + 3 * sizes::spacing);
    taskNameRect.setLeft(option.rect.left() + 3 * sizes::spacing);
    dueDateRect.setLeft(taskNameRect.right() + 2 * sizes::spacing);
    dueDateRect.setRight(option.rect.right() - sizes::checkboxSize + sizes::spacing);
    dueDateRect.setTop(option.rect.top() + 3 * sizes::spacing);
    descriptionRect.setTop(option.rect.top() + 10 * sizes::spacing);
    descriptionRect.setBottom(option.rect.bottom() - 5 * sizes::spacing);
    descriptionRect.setLeft(option.rect.left() + 4 * sizes::spacing);
    descriptionRect.setRight(option.rect.right() - 20 * sizes::spacing);
    checkboxRect.setTop(descriptionRect.bottom() + sizes::spacing);
    checkboxRect.setLeft(option.rect.right() - sizes::checkboxSize - 4 * sizes::spacing);
    checkboxRect.setBottom(option.rect.bottom() - 10 * sizes::spacing);
    checkboxRect.setRight(option.rect.right() - sizes::checkboxSize);

    painter->drawText(taskNameRect, Qt::AlignLeft | Qt::AlignTop, taskName);
    painter->drawText(dueDateRect, Qt::AlignRight | Qt::AlignTop, dueDate.toString("dd.MM.yyyy"));

    QRect descriptionBorderRect = descriptionRect.adjusted(-5, -5, 5, 5);
    QColor borderBlue(195, 224, 229);

    painter->setPen(borderBlue);
    painter->drawRect(descriptionBorderRect);
    painter->drawText(descriptionRect, Qt::AlignLeft | Qt::AlignTop, description);

    QStyleOptionButton checkboxOption;
    checkboxOption.rect = checkboxRect;
    checkboxOption.state = completed ? QStyle::State_On : QStyle::State_Off;
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxOption, painter);
}

QSize CustomItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(100);
    return size;
}

bool CustomItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QRect checkboxRect = option.rect;
        checkboxRect.setTop(option.rect.bottom() - 6 * sizes::spacing);
        checkboxRect.setLeft(option.rect.right() - sizes::checkboxSize - 4 * sizes::spacing);
        checkboxRect.setBottom(option.rect.bottom() - 10 * sizes::spacing);
        checkboxRect.setRight(option.rect.right() - sizes::checkboxSize);

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (checkboxRect.contains(mouseEvent->pos()))
        {
            bool completed = index.data(TaskRoles::CompletedRole).toBool();
            model->setData(index, !completed, TaskRoles::CompletedRole);
            return true;
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

} // namespace TODO
