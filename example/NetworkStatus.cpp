#include "NetworkStatus.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QTimer>
#include <QVBoxLayout>


#include "ElaTableView.h"

#include "NetworkStatusModel.h"

NetworkStatus::NetworkStatus(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);

    //ElaTableView
    _tableView = new ElaTableView(this);
    QFont tableHeaderFont = _tableView->horizontalHeader()->font();
    tableHeaderFont.setPixelSize(16);
    _tableView->horizontalHeader()->setFont(tableHeaderFont);
    _tableView->setModel(new NetworkStatusModel(this));
    _tableView->setAlternatingRowColors(true);
    _tableView->setIconSize(QSize(38, 38));
    _tableView->verticalHeader()->setHidden(true);
    _tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    _tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    _tableView->horizontalHeader()->setMinimumSectionSize(60);
    _tableView->verticalHeader()->setMinimumSectionSize(46);
    _tableView->setFixedHeight(450);
    connect(_tableView, &ElaTableView::tableViewShow, this, [=]() {
        _tableView->setColumnWidth(0, 150);
        _tableView->setColumnWidth(1, 250);
        _tableView->setColumnWidth(2, 250);
        _tableView->setColumnWidth(3, 250);
    });




    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("ElaView");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);

    centerVLayout->addWidget(_tableView);
    centerVLayout->addStretch();


    addCentralWidget(centralWidget, true, false, 0);
}

NetworkStatus::~NetworkStatus()
{
}
