﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ElaWindow.h"
class T_Home;
class DeviceView;
class Scheduling;
class Routing;
class zone;
class T_Icon;
class T_ElaScreen;
class T_BaseComponents;
class T_Navigation;
class T_Popup;
class T_Card;
class T_ListView;
class T_TableView;
class T_TreeView;
class T_About;
class T_Setting;
class ElaContentDialog;
class MainWindow : public ElaWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    Q_SLOT void onCloseButtonClicked();

    void initWindow();
    void initEdgeLayout();
    void initContent();

private:
    T_Home* _homePage{nullptr};
    Scheduling* _scheduling{nullptr};
    DeviceView* _deviceView{nullptr};
    Routing* _routing{nullptr};
    zone* _zone{nullptr};
#ifdef Q_OS_WIN
    T_ElaScreen* _elaScreenPage{nullptr};
#endif
    T_Icon* _iconPage{nullptr};
    T_BaseComponents* _baseComponentsPage{nullptr};
    T_Navigation* _navigationPage{nullptr};

    T_Popup* _popupPage{nullptr};
    T_Card* _cardPage{nullptr};
    T_ListView* _listViewPage{nullptr};
    T_TableView* _tableViewPage{nullptr};
    T_TreeView* _treeViewPage{nullptr};
    T_About* _aboutPage{nullptr};
    T_Setting* _settingPage{nullptr};
    QString _elaDxgiKey{""};
    QString _viewKey{""};
    QString _aboutKey{""};
    QString _settingKey{""};
};
#endif // MAINWINDOW_H
