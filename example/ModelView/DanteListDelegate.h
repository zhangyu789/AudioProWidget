#ifndef DANTELISTDELEGATE_H
#define DANTELISTDELEGATE_H

#include <QStyledItemDelegate>
#include <ElaPushButton.h>
#include <QMouseEvent>

class DanteListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DanteListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void editClicked(const QModelIndex &index);
};

#endif // DANTELISTDELEGATE_H
