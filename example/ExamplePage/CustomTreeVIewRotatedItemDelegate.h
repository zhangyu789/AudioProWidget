#ifndef CUSTOM_TREE_VIEW_ROTATED_ITEM_DELEGATE_H
#define CUSTOM_TREE_VIEW_ROTATED_ITEM_DELEGATE_H

#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QPainter>

class RotatedItemDelegate : public QStyledItemDelegate
{
public:
    RotatedItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        painter->save();

        // 计算旋转中心
        QPoint center = option.rect.center();

        // 设置旋转角度（例如，倾斜 15 度）
        const int angle = 15;

        // 进行旋转变换
        painter->translate(center);
        painter->rotate(angle);
        painter->translate(-center);

        // 调用基类的绘制方法
        QStyledItemDelegate::paint(painter, option, index);

        painter->restore();
    }
};

#endif // CUSTOM_TREE_VIEW_ROTATED_ITEM_DELEGATE_H