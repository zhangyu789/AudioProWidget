#ifndef DEVICELIST_H
#define DEVICELIST_H

#include "ElaScrollPage.h"

class ElaListView;
class ElaTableView;
class ElaTreeView;
class DeviceList : public ElaScrollPage
{
public:
    explicit DeviceList(QWidget* parent = nullptr);
    ~DeviceList();

private:

    ElaTableView* _tableView{nullptr};

};

#endif // DEVICELIST_H
