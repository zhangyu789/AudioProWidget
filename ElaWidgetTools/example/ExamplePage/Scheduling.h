#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "DeviceList.h"
#include "NetworkStatus.h"

#include "ElaScrollPage.h"

class ElaTabWidget;
class Scheduling : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit Scheduling(QWidget* parent = nullptr);
    ~Scheduling();

private:
    ElaTabWidget* _tabWidget{nullptr};

    DeviceList* device{nullptr};
    NetworkStatus* signal{nullptr};

};

#endif // SCHEDULING_H
