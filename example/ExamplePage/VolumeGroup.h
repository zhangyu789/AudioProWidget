#ifndef VOLUMEGROUP_H
#define VOLUMEGROUP_H

#include <QWidget>
#include "GroupWidget.h"

class VolumeGroup : public QWidget {
    Q_OBJECT
public:
    explicit VolumeGroup(QWidget* parent = nullptr);
    ~VolumeGroup();

private:
    GroupWidget* _groupWidget;

    void setupData();
};

#endif // VOLUMEGROUP_H
