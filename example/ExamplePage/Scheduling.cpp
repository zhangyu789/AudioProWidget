#include "Scheduling.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "ElaTabWidget.h"
#include "VolumeGroup.h"
#include "NetworkStatus.h"


Scheduling::Scheduling(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);
    setContentsMargins(20, 20, 0, 0);

    _tabWidget = new ElaTabWidget(this);
    _tabWidget->setTabsClosable(false);
    _tabWidget->setMovable(false);
    _tabWidget->setTabShape(QTabWidget::Rounded);
    _tabWidget->setIsTabTransparent(true);
    // 自定义样式表
    QString styleSheet = "QTabBar::tab {"
                         "   background-color: #F2F6F9;"
                         "   color: black;"
                         "   font-size: 12px;"
                         "   border: 1.2px solid #ACC4DF;"
                         "   border-bottom-color: #ACC4DF;"
                         "   border-top-left-radius: 4px;"
                         "   border-top-right-radius: 4px;"
                         "   border-bottom-left-radius: 4px;"
                         "   border-bottom-right-radius: 4px;"
                         "   min-width: 18ex;"
                         "   padding: 10px;"
                         "   margin-right: 5px;"
                         "   margin-bottom: 20px;"
                         "}"
                         ""
                         "QTabBar::tab:selected {"
                         "   background-color: #2472DD;"
                         "   color: white;"
                         "   font-size: 12px;"
                         "   border: 1px solid #2472DD;"
                         "   border-bottom-color: #2472DD;"
                         "   border-top-left-radius: 4px;"
                         "   border-top-right-radius: 4px;"
                         "   border-bottom-left-radius: 4px;"
                         "   border-bottom-right-radius: 4px;"
                         "   min-width: 18ex;"
                         "   padding: 10px;"
                         "   margin-right: 5px;"
                         "   margin-bottom: 20px;"
                         "}";
    _tabWidget->setStyleSheet(styleSheet);

    group = new VolumeGroup();
    schedule = new NetworkStatus();


    _tabWidget->addTab(group, "Volume group");
    _tabWidget->addTab(schedule, "Volume schedule");

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(_tabWidget);

    addCentralWidget(centralWidget, true, true, 0);
}

Scheduling::~Scheduling()
{
}
