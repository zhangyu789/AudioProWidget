#include "VolumeGroup.h"

VolumeGroup::VolumeGroup(QWidget* parent)
    : QWidget(parent),
    _groupWidget(new GroupWidget(this)) // 初始化 GroupWidget
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _groupWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout->addWidget(_groupWidget);  // 添加 GroupWidget 到布局中

    setLayout(mainLayout);

    setupData();  // 初始化数据
}

VolumeGroup::~VolumeGroup() {
    // Qt 会自动删除子对象，因此不需要手动删除 _groupWidget
}

void VolumeGroup::setupData() {
    _groupWidget->addGroup("Group 1");
    _groupWidget->addTx2("TX2 - 1", "Group 1");
    _groupWidget->addZone("Zone 1", "TX2 - 1", "Group 1");
    _groupWidget->addZone("Zone 2", "TX2 - 1", "Group 1");

    _groupWidget->addTx2("TX2 - 2", "Group 1");
    _groupWidget->addZone("Zone 1", "TX2 - 2", "Group 1");
    _groupWidget->addZone("Zone 2", "TX2 - 2", "Group 1");

    _groupWidget->addGroup("Group 2");
    _groupWidget->addTx2("TX2 - 3", "Group 2");
    _groupWidget->addZone("Zone 1", "TX2 - 3", "Group 2");
    _groupWidget->addZone("Zone 2", "TX2 - 3", "Group 2");
}



