#include "DeviceView.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#include "ElaTabWidget.h"
#include "DeviceList.h"
#include "SignalStrength.h"
#include "NetworkStatus.h"
DeviceView::DeviceView(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);
    setContentsMargins(20, 20, 0, 0);

    _tabWidget = new ElaTabWidget(this);
    _tabWidget->setTabsClosable(false);
    _tabWidget->setMovable(false);
    _tabWidget->setTabShape(QTabWidget::Rounded);
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

    device = new DeviceList();
    signal = new SignalStrength();
    network = new NetworkStatus();

    _tabWidget->addTab(device, "Device List");
    _tabWidget->addTab(signal, "Signal Strength");
    _tabWidget->addTab(network, "Network Status");
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("");
    QVBoxLayout* centerVLayout = new QVBoxLayout(centralWidget);
    centerVLayout->setContentsMargins(0, 0, 0, 0);
    centerVLayout->addWidget(_tabWidget);

    addCentralWidget(centralWidget, true, true, 0);
}

DeviceView::~DeviceView()
{
}
