#ifndef DEVICELIST_H
#define DEVICELIST_H

#include "ElaScrollPage.h"

class ElaListView;
class ElaTableView;
class ElaTreeView;
class T_IconDelegate;
class DeviceListModel;
class DeviceListDelegate;
class DeviceList : public ElaScrollPage
{
public:
    explicit DeviceList(QWidget* parent = nullptr);
    ~DeviceList();

private:
    ElaTableView* _tableView{nullptr};
    DeviceListModel* _deviceListModel;
    DeviceListDelegate* _deviceListDelegate;
        T_IconDelegate* _iconDelegate;

private slots:
    void onButton1Clicked(const QModelIndex &index, const QString &buttonText);
    void onButton2Clicked(const QModelIndex &index, const QString &buttonText);
};

#endif // DEVICELIST_H
