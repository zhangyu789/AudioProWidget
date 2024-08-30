#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include "DeviceList.h"
#include "SignalStrength.h"
#include "NetworkStatus.h"
#include "ElaScrollPage.h"

class ElaTabWidget;
class DeviceView : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit DeviceView(QWidget* parent = nullptr);
    ~DeviceView();

private:
    ElaTabWidget* _tabWidget{nullptr};
    DeviceList* device{nullptr};
    SignalStrength* signal{nullptr};
    NetworkStatus* network{nullptr};
};

#endif // DEVICEVIEW_H
