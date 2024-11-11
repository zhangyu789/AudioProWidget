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
    // Set horizontal size policy to Expanding, vertical to Fixed
    groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // Set the maximum width to be half the parent container width
    groupBox->setMaximumWidth(parentWidget()->width() / 2);

    QVBoxLayout* groupLayout = new QVBoxLayout(groupBox);

    // 创建 TX2 区域的标签并添加
    QLabel* txLabel = new QLabel("TX 2", this);
    txLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    txLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop); // 左上对齐
    groupLayout->addWidget(txLabel);

    // 创建区域布局：TX2 区域
    // 设置 TX2 区域的对齐方式
    QHBoxLayout* txListLayout = new QHBoxLayout;
    txListLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // 将TX2添加到 Group 的总体布局中
    groupLayout->addLayout(txListLayout);

    // 创建 zone 区域的标签并添加
    QLabel* zoneLabel = new QLabel("Zone", this);
    zoneLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    zoneLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop); // 左上对齐
    groupLayout->addWidget(zoneLabel);
    // 创建区域布局： Zone 区域
    // 设置 Zone 区域的对齐方式
    QVBoxLayout* zoneListLayout = new QVBoxLayout;
    zoneListLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    // 将Zone添加到 Group 的总体布局中
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

    // 设置按钮的大小策略为 Fixed，以防止它拉伸
    txButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 将 TX2 按钮添加到 TX2 区域布局中
    _txListLayouts[groupName]->addWidget(txButton);

    connect(txButton, &QPushButton::toggled, this, [=](bool checked) {
        // 切换该 TX2 下所有 Zone 的可见性和对应设备名称的显示状态
        QString key = groupName + "|" + txName;

        if (checked) {
            // 如果还没有显示对应的设备名称标签，创建它并添加到布局
            if (!_txLabels.contains(key)) {
                QLabel* txLabel = new QLabel(txName, this);
                txLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
                _txLabels[key] = txLabel;
                QHBoxLayout* zoneRowLayout = new QHBoxLayout;
                zoneRowLayout->addWidget(txLabel);
                zoneRowLayout->setAlignment(Qt::AlignLeft);

                _zoneListLayouts[groupName]->addLayout(zoneRowLayout);
            }

            // 显示 Zone 按钮和 TX2 标签
            for (auto* zoneButton : _zoneButtons[key]) {
                zoneButton->setVisible(true);
            }
            _txLabels[key]->setVisible(true);
        } else {
            // 隐藏 Zone 按钮和 TX2 标签
            for (auto* zoneButton : _zoneButtons[key]) {
                zoneButton->setVisible(false);
            }
            if (_txLabels.contains(key)) {
                _txLabels[key]->setVisible(false);
            }
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

    // 设置按钮的大小策略为 Fixed
    zoneButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QString key = groupName + "|" + txName;

    // 检查是否需要为此 TX2 设备创建一个新的行布局
    if (_zoneButtons[key].isEmpty()) {
        // 创建一个新的行布局用于显示 TX2 设备的名称和其 Zone 列表
        QHBoxLayout* zoneRowLayout = new QHBoxLayout;

        // 添加占位标签，将设备名称推迟到按钮显示时创建
        QLabel* txLabel = new QLabel(txName, this);
        txLabel->setVisible(false);  // 默认隐藏
        _txLabels[key] = txLabel;
        zoneRowLayout->addWidget(txLabel);

        // 设置 Zone 行的对齐方式
        zoneRowLayout->setAlignment(Qt::AlignLeft);

        // 将此行布局添加到 Zone 区域布局中
        _zoneListLayouts[groupName]->addLayout(zoneRowLayout);
    }

    // 将 Zone 按钮添加到对应的 TX2 行布局中
    _zoneButtons[key].append(zoneButton);
    _zoneListLayouts[groupName]->itemAt(_zoneListLayouts[groupName]->count() - 1)->layout()->addWidget(zoneButton);
}
