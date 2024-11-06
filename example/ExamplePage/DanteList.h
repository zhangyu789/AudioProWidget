#ifndef DANTELIST_H
#define DANTELIST_H

#include "ElaScrollPage.h"

class ElaListView;
class ElaTableView;
class ElaTreeView;
class T_IconDelegate;
class DanteListModel;
class DanteListDelegate;
class DanteList : public ElaScrollPage
{
public:
    explicit DanteList(QWidget* parent = nullptr);
    ~DanteList();

private:
    ElaTableView* _tableView{nullptr};
    DanteListModel* _danteListModel;
    DanteListDelegate* _danteListDelegate;
    T_IconDelegate* _iconDelegate;

private slots:
    void onButton1Clicked(const QModelIndex &index, const QString &buttonText);
    void onButton2Clicked(const QModelIndex &index, const QString &buttonText);
};

#endif // DANTELIST_H
