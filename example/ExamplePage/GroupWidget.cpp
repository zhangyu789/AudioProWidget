#include "GroupWidget.h"
#include <QLabel>
GroupWidget::GroupWidget(QWidget *parent)
    : QWidget(parent),
    _mainLayout(new QVBoxLayout(this))
{
    setLayout(_mainLayout);
}

void GroupWidget::addGroup(const QString& groupName) {
    // 如果该 Group 已经存在，则跳过
    if (_groups.contains(groupName)) return;

    // 创建 Group 的 QGroupBox
    QGroupBox* groupBox = new QGroupBox(groupName, this);
    QVBoxLayout* groupLayout = new QVBoxLayout(groupBox);

    // 创建两个区域布局：TX2 区域和 Zone 区域
    QHBoxLayout* txListLayout = new QHBoxLayout;
    QVBoxLayout* zoneListLayout = new QVBoxLayout;

    // 将这两个布局添加到 Group 的总体布局中
    groupLayout->addLayout(txListLayout);
    groupLayout->addLayout(zoneListLayout);

    // 将 Group 添加到主布局中
    _mainLayout->addWidget(groupBox);
    _groups[groupName] = groupBox;

    // 记录 Group 的 TX2 和 Zone 区域布局
    _txListLayouts[groupName] = txListLayout;
    _zoneListLayouts[groupName] = zoneListLayout;

    groupBox->setLayout(groupLayout);
}

void GroupWidget::addTx2(const QString& txName, const QString& groupName) {
    // 检查 Group 是否存在
    if (!_groups.contains(groupName)) {
        addGroup(groupName); // 如果不存在，先创建 Group
    }

    // 创建 TX2 按钮
    QPushButton* txButton = new QPushButton(txName);
    txButton->setCheckable(true);

    // 将 TX2 按钮添加到 TX2 区域布局中
    _txListLayouts[groupName]->addWidget(txButton);

    connect(txButton, &QPushButton::toggled, this, [=](bool checked) {
        // 切换该 TX2 下所有 Zone 的可见性
        QString key = groupName + "|" + txName;
        for (auto* zoneButton : _zoneButtons[key]) {
            zoneButton->setVisible(checked);
        }
    });
}

void GroupWidget::addZone(const QString& zoneName, const QString& txName, const QString& groupName) {
    // 检查 Group 和 TX2 是否存在
    if (!_groups.contains(groupName) || !_txListLayouts[groupName]) return;

    // 创建 Zone 按钮并设置为隐藏
    QPushButton* zoneButton = new QPushButton(zoneName);
    zoneButton->setCheckable(true);
    zoneButton->setVisible(false);

    QString key = groupName + "|" + txName;

    // 检查是否需要为此 TX2 设备创建一个新的行布局
    if (_zoneButtons[key].isEmpty()) {
        // 创建一个新的行布局用于显示 TX2 设备的名称和其 Zone 列表
        QHBoxLayout* zoneRowLayout = new QHBoxLayout;

        // 在 Zone 列表前添加 TX2 的名称
        QLabel* txLabel = new QLabel(txName, this);
        zoneRowLayout->addWidget(txLabel);

        // 将此行布局添加到 Zone 区域布局中
        _zoneListLayouts[groupName]->addLayout(zoneRowLayout);
    }

    // 将 Zone 按钮添加到对应的 TX2 行布局中
    _zoneButtons[key].append(zoneButton);
    _zoneListLayouts[groupName]->itemAt(_zoneListLayouts[groupName]->count() - 1)->layout()->addWidget(zoneButton);
}
