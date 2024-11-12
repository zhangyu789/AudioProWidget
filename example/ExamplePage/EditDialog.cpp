#include "EditDialog.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QComboBox>
#include <QLineEdit>
#include "ElaComboBox.h"

EditDialog::EditDialog(ElaWidget *parent)
    : ElaWidget(parent)
{
    setWindowTitle("Edit");
    setWindowIcon(QIcon(":/icon/edit.png"));

    QString buttonStyle = R"(
        QPushButton {
            background-color: #007bff;    /* 按钮背景色 */
            color: white;                 /* 文字颜色 */
            border-radius: 5px;           /* 圆角边框 */
            font-size: 14px;              /* 字体大小 */
            padding: 8px 12px;
        }
        QPushButton:hover {
            background-color: #0056b3;    /* 悬停时的背景色 */
        }
        QPushButton:pressed {
            background-color: #003d80;    /* 点击时的背景色 */
        }
    )";

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

    // Apply style sheet to buttons
    backupBtn->setStyleSheet(buttonStyle);
    updateFWBtn->setStyleSheet(buttonStyle);
    restoreBtn->setStyleSheet(buttonStyle);
    pairBtn->setStyleSheet(buttonStyle);
    rebootBtn->setStyleSheet(buttonStyle);

    operateLayout->addWidget(backupBtn);
    operateLayout->addWidget(updateFWBtn);
    operateLayout->addWidget(restoreBtn);
    operateLayout->addWidget(pairBtn);
    operateLayout->addWidget(rebootBtn);
    operateLayout->setSpacing(10);  // 控件之间的间距
    operateGroup->setLayout(operateLayout);

    // Transmit Power Group
    QGroupBox *powerGroup = new QGroupBox("Transmit Power");
    QVBoxLayout *powerLayout = new QVBoxLayout;
    powerComboBox = new ElaComboBox;
    powerComboBox->addItems({"22 dBm", "20 dBm", "12 dBm"});
    powerComboBox->setFixedSize(120, 40);
    powerLayout->addWidget(powerComboBox);
    powerGroup->setLayout(powerLayout);

    // Addresses Group
    QGroupBox *addressesGroup = new QGroupBox("Addresses");
    QVBoxLayout *addressesLayout = new QVBoxLayout;
    autoIPRadio = new ElaRadioButton("Obtain an IP Address Automatically (default)");
    manualIPRadio = new ElaRadioButton("Manually configure an IP Address");

    addressesLayout->addWidget(autoIPRadio);
    addressesLayout->addWidget(manualIPRadio);

    // Helper function to create each row of address input fields
    auto createAddressRow = [](const QString &labelText) {
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(new QLabel(labelText));

        for (int i = 0; i < 4; ++i) {
            QLineEdit *edit = new QLineEdit;
            edit->setFixedWidth(30);   // Width for each IP segment
            edit->setMaxLength(3);     // Limit to 3 characters for each segment
            layout->addWidget(edit);

            if (i < 3) {
                layout->addWidget(new QLabel("."));  // Dot separator
            }
        }
        layout->addStretch();
        return layout;
    };

    // Adding each row to the addresses layout
    addressesLayout->addLayout(createAddressRow("IP Address:"));
    addressesLayout->addLayout(createAddressRow("Netmask:"));
    addressesLayout->addLayout(createAddressRow("DNS Server:"));
    addressesLayout->addLayout(createAddressRow("Gateway:"));

    // Apply and Revert buttons
    QHBoxLayout *applyRevertLayout = new QHBoxLayout;
    applyBtn = new QPushButton("Apply");
    revertBtn = new QPushButton("Revert");
    applyBtn->setFixedSize(100, 40);
    revertBtn->setFixedSize(100, 40);
    applyBtn->setStyleSheet(buttonStyle);
    revertBtn->setStyleSheet(buttonStyle);
    applyRevertLayout->addWidget(applyBtn);
    applyRevertLayout->addWidget(revertBtn);
    applyRevertLayout->setSpacing(10);

    addressesLayout->addLayout(applyRevertLayout);
    addressesGroup->setLayout(addressesLayout);

    // Main Layout
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;

    leftLayout->addWidget(operateGroup);
    leftLayout->addWidget(powerGroup);
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(addressesGroup);

    setLayout(mainLayout);
}
