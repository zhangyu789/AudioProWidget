#include "DanteListDelegate.h"
#include <QPushButton>
#include <QPainter>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QDebug>
#include <QFontMetrics>
#include <QPen>
#include <QBrush>

DanteListDelegate::DanteListDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void DanteListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton buttonStyle1;
    buttonStyle1.text = "Edit";

    QFontMetrics fm(painter->font());
    int buttonWidth1 = fm.horizontalAdvance(buttonStyle1.text) + 20;
    int buttonHeight = fm.height() + 10; // Adjust height for padding

    int totalButtonWidth = buttonWidth1 + 10; // Including space between buttons
    int totalButtonHeight = buttonHeight; // Assuming same height for both buttons

    // Calculate the center position
    int xOffset = (option.rect.width() - totalButtonWidth) / 2;
    int yOffset = (option.rect.height() - totalButtonHeight) / 2;

    buttonStyle1.rect = QRect(option.rect.x() + xOffset, option.rect.y() + yOffset, buttonWidth1, buttonHeight);


    buttonStyle1.state = QStyle::State_Enabled | QStyle::State_Raised;

    QPalette palette;
    palette.setColor(QPalette::ButtonText, QColor("#2472DD"));
    palette.setColor(QPalette::Button, QColor("#e0e9f9"));

    buttonStyle1.palette = palette;


    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(QColor("#2472DD"), 2));
    painter->setBrush(QBrush(QColor("#e0e9f9")));

    // Draw rounded rectangle buttons
    int radius = 4; // Corner radius
    painter->drawRoundedRect(buttonStyle1.rect, radius, radius);


    // Draw text
    painter->setPen(QColor("#2472DD"));
    painter->drawText(buttonStyle1.rect, Qt::AlignCenter, buttonStyle1.text);

}

bool DanteListDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() != QEvent::MouseButtonPress)
        return QStyledItemDelegate::editorEvent(event, model, option, index);

    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

    QFontMetrics fm(option.font);
    int buttonWidth1 = fm.horizontalAdvance("Edit") + 20;
    int buttonHeight = fm.height() + 10; // Adjust height for padding

    int totalButtonWidth = buttonWidth1 + 10; // Including space between buttons
    int totalButtonHeight = buttonHeight; // Assuming same height for both buttons

    // Calculate the center position
    int xOffset = (option.rect.width() - totalButtonWidth) / 2;
    int yOffset = (option.rect.height() - totalButtonHeight) / 2;

    QRect button1Rect = QRect(option.rect.x() + xOffset, option.rect.y() + yOffset, buttonWidth1, buttonHeight);

    int radius = 10; // Corner radius
    if (button1Rect.contains(mouseEvent->pos()) && button1Rect.adjusted(1, 1, -1, -1).contains(mouseEvent->pos()))
    {
        emit button1Clicked(index);
        qDebug() << "Button 1 of item at row" << index.row() + 1 << "clicked";
    }

    return true;
}
