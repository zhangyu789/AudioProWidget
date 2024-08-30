#ifndef DEVICELISTDELEGATE_H
#define DEVICELISTDELEGATE_H

#include <QStyledItemDelegate>

class DeviceListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DeviceListDelegate(QObject *parent = nullptr);
    ~DeviceListDelegate();

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
         // 可以在这里添加成员变量
};

#endif // DEVICELISTDELEGATE_H
