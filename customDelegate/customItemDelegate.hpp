#ifndef CUSTOMITEMDELEGATE_HPP
#define CUSTOMITEMDELEGATE_HPP

#include <QMouseEvent>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

namespace TODO {

class TaskModel;

class CustomItemDelegate : public QStyledItemDelegate {
public:
    CustomItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;    
};

} // namespace TODO

#endif // CUSTOMITEMDELEGATE_HPP
