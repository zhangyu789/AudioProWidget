#include "DeviceListDelegate.h"

#include <QPainter>
#include <QPushButton>
#include <QApplication>
#include <QStyleOptionButton>

DeviceListDelegate::DeviceListDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

DeviceListDelegate::~DeviceListDelegate()
{
}

void DeviceListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QRect rect = option.rect;
    // 分割矩形区域来放置两个按钮
    int halfWidth = rect.width() / 2;
    rect.setWidth(halfWidth);

    // 绘制第一个按钮
    QPushButton button1("Edit");
    QStyleOptionButton opt1;
    opt1.rect = rect.adjusted(5, 5, -5, -5); // 调整边距
    opt1.state |= QStyle::State_Enabled;
    QApplication::style()->drawControl(QStyle::CE_PushButton, &opt1, painter);

    // 移动矩形位置来绘制第二个按钮
    rect.moveLeft(rect.right());
    QPushButton button2("Multicast");
    QStyleOptionButton opt2;
    opt2.rect = rect.adjusted(5, 5, -5, -5); // 调整边距
    opt2.state |= QStyle::State_Enabled;
    QApplication::style()->drawControl(QStyle::CE_PushButton, &opt2, painter);

    painter->restore();
}

QSize DeviceListDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 返回一个合适的大小提示，这可能需要根据实际情况调整
    return QSize(100, 30);
}
