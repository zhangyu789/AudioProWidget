#ifndef DEVICELISTDELEGATE_H
#define DEVICELISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include <QMouseEvent>

class DeviceListDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DeviceListDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void button1Clicked(const QModelIndex &index);
    void button2Clicked(const QModelIndex &index);
};

#endif // DEVICELISTDELEGATE_H
