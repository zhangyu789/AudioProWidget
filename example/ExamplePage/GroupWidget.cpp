#include "GroupWidget.h"

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

    // 将 Group 添加到主布局中
    _mainLayout->addWidget(groupBox);
    _groups[groupName] = groupBox; // 存储 Group Box 以便后续查找

    // 初始化该 Group 的 TX2 布局映射
    _txLayouts[groupName] = QMap<QString, QHBoxLayout*>();

    // 设置 groupBox 的布局
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

    // 创建 TX2 的布局
    QHBoxLayout* txLayout = new QHBoxLayout;
    txLayout->addWidget(txButton);

    // 获取 Group 的布局
    QVBoxLayout* groupLayout = qobject_cast<QVBoxLayout*>(_groups[groupName]->layout());
    if (groupLayout) {
        groupLayout->addLayout(txLayout);  // 将 TX2 布局添加到 Group 的布局中
    }

    // 保存 TX2 布局
    _txLayouts[groupName][txName] = txLayout;

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
    if (!_txLayouts.contains(groupName) || !_txLayouts[groupName].contains(txName)) return;

    // 创建 Zone 按钮并添加到对应的 TX2 布局中
    QPushButton* zoneButton = new QPushButton(zoneName);
    zoneButton->setCheckable(true);
    zoneButton->setVisible(false); // 默认隐藏

    QString key = groupName + "|" + txName;
    _txLayouts[groupName][txName]->addWidget(zoneButton); // 添加到 TX2 布局中
    _zoneButtons[key].append(zoneButton); // 存储 Zone 按钮以便管理
}
