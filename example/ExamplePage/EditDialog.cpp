#include "EditDialog.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

EditDialog::EditDialog(ElaWidget *parent)
    : ElaWidget(parent)
{
    setWindowTitle("Edit");
    setWindowIcon(QIcon(":/icon/edit.png"));

    // Operate Group
    QGroupBox *operateGroup = new QGroupBox("Operate");
    QVBoxLayout *operateLayout = new QVBoxLayout;
    backupBtn = new QPushButton("Backup");
    updateFWBtn = new QPushButton("Update FW");
    restoreBtn = new QPushButton("Restore");
    pairBtn = new QPushButton("Pair");
    rebootBtn = new QPushButton("Reboot");

    backupBtn->setFixedSize(100, 40);
    updateFWBtn->setFixedSize(100, 40);
    restoreBtn->setFixedSize(100, 40);
    pairBtn->setFixedSize(100, 40);
    rebootBtn->setFixedSize(100, 40);

    operateLayout->addWidget(backupBtn);
    operateLayout->addWidget(updateFWBtn);
    operateLayout->addWidget(restoreBtn);
    operateLayout->addWidget(pairBtn);
    operateLayout->addWidget(rebootBtn);
    operateLayout->setSpacing(10);  // 控件之间的间距
    operateGroup->setLayout(operateLayout);

    // Addresses Group
    QGroupBox *addressesGroup = new QGroupBox("Addresses");
    QVBoxLayout *addressesLayout = new QVBoxLayout;
    autoIPRadio = new QRadioButton("Obtain an IP Address Automatically (default)");
    manualIPRadio = new QRadioButton("Manually configure an IP Address");

    QHBoxLayout *ipLayout = new QHBoxLayout;
    ipEdit = new QLineEdit;
    netmaskEdit = new QLineEdit;
    dnsEdit = new QLineEdit;
    gatewayEdit = new QLineEdit;
    ipEdit->setFixedWidth(40);
    netmaskEdit->setFixedWidth(40);
    dnsEdit->setFixedWidth(40);
    gatewayEdit->setFixedWidth(40);

    ipLayout->addWidget(new QLabel("IP Address:"));
    ipLayout->addWidget(ipEdit);
    ipLayout->addWidget(new QLabel("."));
    ipLayout->addWidget(netmaskEdit);
    ipLayout->addWidget(new QLabel("."));
    ipLayout->addWidget(dnsEdit);
    ipLayout->addWidget(new QLabel("."));
    ipLayout->addWidget(gatewayEdit);

    QHBoxLayout *applyRevertLayout = new QHBoxLayout;
    applyBtn = new QPushButton("Apply");
    revertBtn = new QPushButton("Revert");
    applyBtn->setFixedSize(100, 40);
    revertBtn->setFixedSize(100, 40);
    applyRevertLayout->addWidget(applyBtn);
    applyRevertLayout->addWidget(revertBtn);
    applyRevertLayout->setSpacing(10);

    addressesLayout->addWidget(autoIPRadio);
    addressesLayout->addWidget(manualIPRadio);
    addressesLayout->addLayout(ipLayout);
    addressesLayout->addLayout(applyRevertLayout);
    addressesGroup->setLayout(addressesLayout);

    // Transmit Power Group
    QGroupBox *powerGroup = new QGroupBox("Transmit Power");
    QVBoxLayout *powerLayout = new QVBoxLayout;
    powerComboBox = new QComboBox;
    powerComboBox->addItems({"22 dBm", "20 dBm", "12 dBm"});
    powerComboBox->setFixedSize(120, 40);
    powerLayout->addWidget(powerComboBox);
    powerGroup->setLayout(powerLayout);

    // Main Layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;

    leftLayout->addWidget(operateGroup);
    leftLayout->addWidget(powerGroup);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(addressesGroup);


    setLayout(mainLayout);
}
