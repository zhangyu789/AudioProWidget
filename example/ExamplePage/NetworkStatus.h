#ifndef NetworkStatus_H
#define NetworkStatus_H

#include "ElaScrollPage.h"

class ElaListView;
class ElaTableView;
class ElaTreeView;
class NetworkStatus : public ElaScrollPage
{
public:
    explicit NetworkStatus(QWidget* parent = nullptr);
    ~NetworkStatus();

private:

    ElaTableView* _tableView{nullptr};

};

#endif // DEVICE_H
