#include "DanteList.h"
#include "EditDialog.h"

#include <QApplication>
#include <QClipboard>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTimer>
#include <QVBoxLayout>


#include "ElaTableView.h"
#include "ElaMessageBar.h"
#include "DanteListModel.h"
#include "DanteListDelegate.h"
#include "T_IconDelegate.h"

DanteList::DanteList(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);
    setContentsMargins(0, 0, 0, 0);

    //ElaTableView
    _tableView = new ElaTableView(this);
    _danteListModel = new DanteListModel(this);
    _danteListDelegate = new DanteListDelegate(this);
    QFont tableHeaderFont = _tableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(12);
    _tableView->horizontalHeader()->setFont(tableHeaderFont);
    _tableView->setModel(_danteListModel);
    _iconDelegate = new T_IconDelegate(this);
    // 设置最后一列为操作列，并为其设置自定义委托
    EditDialog* dialog = new EditDialog();
    dialog->hide();
    connect(_danteListDelegate, &DanteListDelegate::editClicked, this, [=](const QModelIndex& index) {
        QString deviceName = _danteListModel->getNameFromModelIndex(index);
        if (deviceName.isEmpty())
        {
            return;
        }
        qApp->clipboard()->setText(deviceName);
        ElaMessageBar::success(ElaMessageBarType::Top, "复制完成", deviceName + "已被复制到剪贴板", 1000, this);


        dialog->setFixedSize(400, 400);
        dialog->moveToCenter();
        dialog->show();

    });

    _tableView->setItemDelegateForColumn(_danteListModel->columnCount() - 1, _danteListDelegate);
    // _tableView->installEventFilter(_danteListDelegate);


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

DanteList::~DanteList()
{
}

void DanteList::onEditClicked(const QModelIndex &index, const QString &buttonText)
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
