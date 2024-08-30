#include "devicelistdelegate.h"
#include "QPushButton"

DeviceListDelegate::DeviceListDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void DeviceListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int buttonWidth = option.rect.width() / 2;
    int buttonHeight = option.rect.height();

    QStyleOptionButton buttonStyle1, buttonStyle2;
    buttonStyle1.text = "Edit";
    buttonStyle2.text = "Multicast";

    // 创建一个样式表字符串
    QString buttonStyleSheet = "QPushButton {"
                               "    color: #2472DD;"
                               "    background-color: #E0E9F9;"
                               "    border: 1px solid #2472DD;"
                               "}";
    buttonStyle1.rect = QRect(option.rect.x(), option.rect.y(), buttonWidth, buttonHeight);
    buttonStyle1.state = QStyle::State_Enabled | QStyle::State_Raised;

    buttonStyle2.rect = QRect(option.rect.x() + buttonWidth, option.rect.y(), buttonWidth, buttonHeight);
    buttonStyle2.state = QStyle::State_Enabled | QStyle::State_Raised;

    QPushButton button1, button2;
    button1.style()->drawControl(QStyle::CE_PushButton, &buttonStyle1, painter, &button1);
    button2.style()->drawControl(QStyle::CE_PushButton, &buttonStyle2, painter, &button2);
}

bool DeviceListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() != QEvent::MouseButtonPress)
        return QStyledItemDelegate::editorEvent(event, model, option, index);

    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    int buttonWidth = option.rect.width() / 2;

    if (option.rect.contains(mouseEvent->pos()))
    {
        // 获取当前索引所在的行号
        int row = index.row();

        // 计算两个按钮的边界
        QRect button1Rect = QRect(option.rect.x(), option.rect.y(), buttonWidth, option.rect.height());
        QRect button2Rect = QRect(option.rect.x() + buttonWidth, option.rect.y(), buttonWidth, option.rect.height());

        if (button1Rect.contains(mouseEvent->pos()))
        {
            emit button1Clicked(index);
            qDebug() << "Button 1 of item at row" << row + 1 << "clicked";
        }
        else if (button2Rect.contains(mouseEvent->pos()))
        {
            emit button2Clicked(index);
            qDebug() << "Button 2 of item at row" << row + 1 << "clicked";
        }
    }

    return true;
}
