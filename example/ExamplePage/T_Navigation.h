#ifndef T_NAVIGATION_H
#define T_NAVIGATION_H

#include "T_BasePage.h"

class DeviceList;
class ElaPivot;
class QTabWidget;
class ElaBreadcrumbBar;
class T_Navigation : public T_BasePage
{
    Q_OBJECT
public:
    explicit T_Navigation(QWidget* parent = nullptr);
    ~T_Navigation();

private:
    ElaBreadcrumbBar* _breadcrumbBar{nullptr};
    ElaPivot* _pivot{nullptr};
    QTabWidget* _tabWidget{nullptr};
};

#endif // T_NAVIGATION_H
