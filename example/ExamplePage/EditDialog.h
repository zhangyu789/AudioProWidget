#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "ElaWidget.h"  // 继承自 ElaWidget

class EditDialog : public ElaWidget {
    Q_OBJECT
public:
    explicit EditDialog(ElaWidget *parent = nullptr);  // 修改构造函数

    // 获取 IP 配置编辑控件的函数
    QLineEdit* getIpEdit() { return ipEdit; }
    QLineEdit* getNetmaskEdit() { return netmaskEdit; }
    QLineEdit* getDnsEdit() { return dnsEdit; }
    QLineEdit* getGatewayEdit() { return gatewayEdit; }

private:
    QPushButton *backupBtn, *restoreBtn, *rebootBtn, *updateFWBtn, *pairBtn;
    QRadioButton *autoIPRadio, *manualIPRadio;
    QLineEdit *ipEdit, *netmaskEdit, *dnsEdit, *gatewayEdit;
    QPushButton *applyBtn, *revertBtn;
    QComboBox *powerComboBox;
};

#endif // EDITDIALOG_H
