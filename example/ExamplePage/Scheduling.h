#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "VolumeGroup.h"
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

    VolumeGroup* group{nullptr};
    NetworkStatus* schedule{nullptr};

};

#endif // SCHEDULING_H
