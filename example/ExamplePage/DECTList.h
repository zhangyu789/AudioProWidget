#ifndef DECTLIST_H
#define DECTLIST_H

#include "ElaScrollPage.h"

class ElaListView;
class ElaTableView;
class ElaTreeView;
class DECTList : public ElaScrollPage
{
public:
    explicit DECTList(QWidget* parent = nullptr);
    ~DECTList();

private:

    ElaTableView* _tableView{nullptr};

};

#endif // DECTLIST_H
