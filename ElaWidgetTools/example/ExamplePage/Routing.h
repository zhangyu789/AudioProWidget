#ifndef ROUTING_H
#define ROUTING_H
#include "ElaScrollPage.h"

class QWebEngineView;
class ElaComboBox;
class ElaSlider;
class Routing : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit Routing(QWidget* parent = nullptr);

private:
    QWebEngineView* _webEngineView{nullptr};

Q_SIGNALS:
    Q_SIGNAL void elaScreenNavigation();
    Q_SIGNAL void elaBaseComponentNavigation();
    Q_SIGNAL void elaSceneNavigation();
    Q_SIGNAL void elaCardNavigation();
    Q_SIGNAL void elaIconNavigation();

};


#endif // ROUTING_H
