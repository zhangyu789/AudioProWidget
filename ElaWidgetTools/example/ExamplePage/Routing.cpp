#include "Routing.h"

#include <QDebug>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QMainWindow>
// #include <QWebEngineView>
// #include <QWebEnginePage>
// #include <QWebEngineSettings>

#include "ElaCheckBox.h"
#include "ElaComboBox.h"
#include "ElaMessageButton.h"
#include "ElaMultiSelectComboBox.h"
#include "ElaPlainTextEdit.h"
#include "ElaProgressBar.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaSlider.h"
#include "ElaSpinBox.h"
#include "ElaText.h"
#include "ElaToggleButton.h"
#include "ElaToggleSwitch.h"

Routing::Routing(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);
    setAttribute(Qt::WA_DontCreateNativeAncestors);

    // // 创建并初始化Web视图
    // _webEngineView = new QWebEngineView(parent);
    // _webEngineView->load(QUrl("http://www.github.com"));
    // _webEngineView->setFixedSize(parent->width(), parent->height()-100);
    // // 设置窗口标志
    // _webEngineView->setAttribute(Qt::WA_DontCreateNativeAncestors);
    // // 隐藏滚动条
    // QWebEnginePage* page = _webEngineView->page();
    // if (page) {
    //     QWebEngineSettings* settings = page->settings();
    //     settings->setAttribute(QWebEngineSettings::ShowScrollBars, false);
    // }

    // 创建中心部件并设置窗口标题为空
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("");

    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    // centerLayout->addWidget(_webEngineView); // 添加Web视图


    // 使Web视图占据所有可用空间
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(0);

    // 添加拉伸因子以使Web视图充满整个布局
    centerLayout->addStretch();

    addCentralWidget(centralWidget, true, true, 0);
}
