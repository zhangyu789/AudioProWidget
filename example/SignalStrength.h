#ifndef SignalStrength_H
#define SignalStrength_H

#include "ElaScrollPage.h"

class ElaListView;
class ElaTableView;
class ElaTreeView;
class SignalStrength : public ElaScrollPage
{
public:
    explicit SignalStrength(QWidget* parent = nullptr);
    ~SignalStrength();

private:

    ElaTableView* _tableView{nullptr};

};

#endif // SignalStrength
