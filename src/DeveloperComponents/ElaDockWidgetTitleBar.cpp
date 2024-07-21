#include "ElaDockWidgetTitleBar.h"

#include <QHBoxLayout>
#include <QPainter>

#include "ElaApplication.h"
#include "ElaDockWidget.h"
#include "ElaIconButton.h"
#include "ElaText.h"
ElaDockWidgetTitleBar::ElaDockWidgetTitleBar(QWidget* parent)
    : QWidget{parent}
{
    _dockWidget = dynamic_cast<ElaDockWidget*>(parent);
    _iconLabel = new QLabel(this);
    _iconLabel->setPixmap(_dockWidget->windowIcon().pixmap(QSize(18, 18)));
    _titleLabel = new ElaText(_dockWidget->windowTitle(), this);
    _titleLabel->setWordWrap(false);
    _titleLabel->setTextPixelSize(13);

    _floatButton = new ElaIconButton(ElaIconType::WindowRestore, 13, 32, 26, this);
    _floatButton->setLightHoverColor(QColor(0xEF, 0xE6, 0xED));
    connect(_floatButton, &ElaIconButton::clicked, this, &ElaDockWidgetTitleBar::onFloatButtonClicked);
    _closeButton = new ElaIconButton(ElaIconType::Xmark, 17, 32, 26, this);
    _closeButton->setLightHoverColor(QColor(0xC4, 0x2B, 0x1C));
    _closeButton->setDarkHoverColor(QColor(0xC4, 0x2B, 0x1C));
    connect(_closeButton, &ElaIconButton::clicked, this, &ElaDockWidgetTitleBar::onCloseButtonClicked);

    _setVisibleFromFeatures(_dockWidget->features());
    connect(_dockWidget, &QDockWidget::featuresChanged, this, [=](QDockWidget::DockWidgetFeatures features) {
        _setVisibleFromFeatures(features);
    });
    connect(_dockWidget, &QDockWidget::windowTitleChanged, this, [=](const QString& title) {
        _titleLabel->setText(title);
    });
    connect(_dockWidget, &QDockWidget::windowIconChanged, this, [=](const QIcon& icon) {
        _iconLabel->setPixmap(icon.pixmap(QSize(18, 18)));
    });

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(_iconLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(_titleLabel);
    mainLayout->addSpacing(10);
    mainLayout->addStretch();
    mainLayout->addWidget(_floatButton);
    mainLayout->addWidget(_closeButton);

    //主题变更
    _themeMode = eApp->getThemeMode();
    connect(eApp, &ElaApplication::themeModeChanged, this, [=](ElaApplicationType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
}

ElaDockWidgetTitleBar::~ElaDockWidgetTitleBar()
{
}

void ElaDockWidgetTitleBar::onFloatButtonClicked()
{
    _dockWidget->setFloating(_dockWidget->isFloating() ? false : true);
}

void ElaDockWidgetTitleBar::onCloseButtonClicked()
{
    _dockWidget->close();
}

void ElaDockWidgetTitleBar::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(_dockWidget->isFloating() ? Qt::transparent : _themeMode == ElaApplicationType::Light ? QColor(0xF5, 0xF1, 0xFF)
                                                                                                           : QColor(0x40, 0x40, 0x40));
    painter.drawRect(rect());
    painter.restore();
}

void ElaDockWidgetTitleBar::_setVisibleFromFeatures(QDockWidget::DockWidgetFeatures features)
{
    _floatButton->setVisible(features.testFlag(QDockWidget::DockWidgetFloatable));
    _closeButton->setVisible(features.testFlag(QDockWidget::DockWidgetClosable));
}
