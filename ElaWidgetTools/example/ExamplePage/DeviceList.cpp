#include "DeviceList.h"

#include <QApplication>
#include <QClipboard>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTimer>
#include <QVBoxLayout>


#include "ElaTableView.h"
#include "ElaMessageBar.h"
#include "DeviceListModel.h"
#include "DeviceListDelegate.h"
#include "T_IconDelegate.h"

DeviceList::DeviceList(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);
    setContentsMargins(0, 0, 0, 0);

    //ElaTableView
    _tableView = new ElaTableView(this);
    _deviceListModel = new DeviceListModel(this);
    _deviceListDelegate = new DeviceListDelegate(this);
    QFont tableHeaderFont = _tableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(12);
    _tableView->horizontalHeader()->setFont(tableHeaderFont);
    _tableView->setModel(_deviceListModel);
        _iconDelegate = new T_IconDelegate(this);
    // 设置最后一列为操作列，并为其设置自定义委托
    connect(_deviceListDelegate, &DeviceListDelegate::button1Clicked, this, [=](const QModelIndex& index) {
        QString deviceName = _deviceListModel->getNameFromModelIndex(index);
        if (deviceName.isEmpty())
        {
            return;
        }
        qApp->clipboard()->setText(deviceName);
        ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", deviceName + "已被复制到剪贴板", 1000, this);
    });
    connect(_deviceListDelegate, &DeviceListDelegate::button2Clicked, this, [=](const QModelIndex& index) {
        QString deviceType = _deviceListModel->getTypeFromModelIndex(index);
        if (deviceType.isEmpty())
        {
            return;
        }
        qApp->clipboard()->setText(deviceType);
        ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", deviceType + "已被复制到剪贴板", 1000, this);
    });
    _tableView->setItemDelegateForColumn(_deviceListModel->columnCount() - 1, _deviceListDelegate);
    // _tableView->installEventFilter(_deviceListDelegate);


    _tableView->setAlternatingRowColors(true);
    _tableView->verticalHeader()->setHidden(true);
    _tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _tableView->horizontalHeader()->setMinimumSectionSize(80);
    _tableView->horizontalHeader()->setMaximumSectionSize(150);
    _tableView->verticalHeader()->setMinimumSectionSize(46);
    _tableView->setFixedHeight(550);
    // _tableView->setStyleSheet("QWidget { border: none; }");

    connect(_tableView, &ElaTableView::tableViewShow, this, [=]() {
        _tableView->setColumnWidth(0, 110);
        _tableView->setColumnWidth(1, 110);
        _tableView->setColumnWidth(2, 110);
        _tableView->setColumnWidth(3, 90);
        _tableView->setColumnWidth(4, 130);
        _tableView->setColumnWidth(5, 110);
        _tableView->setColumnWidth(6, 140);
        _tableView->setColumnWidth(7, 150);
    });




    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);

    centerVLayout->addWidget(_tableView);
    centerVLayout->addStretch();


    addCentralWidget(centralWidget, true, false, 0);
}

DeviceList::~DeviceList()
{
}

void DeviceList::onButton1Clicked(const QModelIndex &index, const QString &buttonText)
{
    //qDebug() << "Button clicked with text:" << buttonText;
    if (buttonText == "Edit")
    {
        // 处理编辑逻辑
        //qDebug() << "Handling Edit button logic.";
        ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", buttonText + "已被复制到剪贴板", 1000, this);
    }
    else
    {
        //qDebug() << "Unknown button text:" << buttonText;
    }
}
void DeviceList::onButton2Clicked(const QModelIndex &index, const QString &buttonText)
{
    //qDebug() << "Button clicked with text:" << buttonText;
    if (buttonText == "Edit")
    {
        // 处理编辑逻辑
        //qDebug() << "Handling Edit button logic.";
        ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", buttonText + "已被复制到剪贴板", 1000, this);
    }
    else
    {
        //qDebug() << "Unknown button text:" << buttonText;
    }
}
