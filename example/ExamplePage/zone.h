#ifndef ZONE_H
#define ZONE_H
#include "ElaScrollPage.h"

class ElaComboBox;
class ElaSlider;
class zone : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit zone(QWidget* parent = nullptr);

private:
    ElaComboBox* _comboBox{nullptr};
    ElaSlider* _masterVolume{nullptr};
    ElaSlider* _zone1{nullptr};
    ElaSlider* _zone2{nullptr};
    ElaSlider* _zone3{nullptr};
    ElaSlider* _zone4{nullptr};
    ElaSlider* _zone5{nullptr};
    ElaSlider* _zone6{nullptr};

Q_SIGNALS:
    Q_SIGNAL void elaScreenNavigation();
    Q_SIGNAL void elaBaseComponentNavigation();
    Q_SIGNAL void elaSceneNavigation();
    Q_SIGNAL void elaCardNavigation();
    Q_SIGNAL void elaIconNavigation();

};


#endif // ZONE_H
