#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include "DanteList.h"
#include "DECTList.h"
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
    DanteList* _dante{nullptr};
    DECTList* _dect{nullptr};
};

#endif // DEVICEVIEW_H
