#include "DeviceList.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QTimer>
#include <QVBoxLayout>


#include "ElaTableView.h"

#include "DeviceListModel.h"

DeviceList::DeviceList(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);
    setContentsMargins(0, 0, 0, 0);

    //ElaTableView
    _tableView = new ElaTableView(this);
    QFont tableHeaderFont = _tableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(16);
    _tableView->horizontalHeader()->setFont(tableHeaderFont);
    _tableView->setModel(new DeviceListModel(this));
    _tableView->setAlternatingRowColors(true);
    _tableView->verticalHeader()->setHidden(true);
    _tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _tableView->horizontalHeader()->setMinimumSectionSize(60);
    _tableView->verticalHeader()->setMinimumSectionSize(46);
    _tableView->setFixedHeight(450);
    // _tableView->setStyleSheet("QWidget { border: none; }");

    connect(_tableView, &ElaTableView::tableViewShow, this, [=]() {
        _tableView->setColumnWidth(0, 120);
        _tableView->setColumnWidth(1, 120);
        _tableView->setColumnWidth(2, 120);
        _tableView->setColumnWidth(3, 100);
        _tableView->setColumnWidth(4, 150);
        _tableView->setColumnWidth(5, 120);
        _tableView->setColumnWidth(6, 150);
        _tableView->setColumnWidth(7, 80);
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
