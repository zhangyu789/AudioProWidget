#include "zone.h"

#include <QDebug>
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QMainWindow>

#include "ElaCheckBox.h"
#include "ElaComboBox.h"
#include "ElaMessageButton.h"
#include "ElaMultiSelectComboBox.h"
#include "ElaPlainTextEdit.h"
#include "ElaProgressBar.h"
#include "ElaRadioButton.h"
#include "ElaScrollPageArea.h"
#include "ElaSlider.h"
#include "ElaSpinBox.h"
#include "ElaText.h"
#include "ElaToggleButton.h"
#include "ElaToggleSwitch.h"

zone::zone(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);
    _comboBox = new ElaComboBox(this);
    QStringList comboList{
                          "TX2-1",
                          "TX2-2",
                          "TX2-3",
                          "TX2-4"};
    _comboBox->addItems(comboList);
    _comboBox->setFixedWidth(150);
    QHBoxLayout* comboBoxLayout = new QHBoxLayout(this);
    comboBoxLayout->addWidget(_comboBox);
    comboBoxLayout->addStretch();
    comboBoxLayout->addSpacing(10);


    _masterVolume = new ElaSlider(this);
    _masterVolume->setOrientation(Qt::Vertical);
    _zone1 = new ElaSlider(this);
    _zone1->setOrientation(Qt::Vertical);
    _zone2 = new ElaSlider(this);
    _zone2->setOrientation(Qt::Vertical);
    _zone3 = new ElaSlider(this);
    _zone3->setOrientation(Qt::Vertical);
    _zone4 = new ElaSlider(this);
    _zone4->setOrientation(Qt::Vertical);
    _zone5 = new ElaSlider(this);
    _zone5->setOrientation(Qt::Vertical);
    _zone6 = new ElaSlider(this);
    _zone6->setOrientation(Qt::Vertical);
    QHBoxLayout* sliderLayout = new QHBoxLayout(this);
    sliderLayout->addSpacing(100);
    sliderLayout->addWidget(_masterVolume);
    sliderLayout->addSpacing(200);
    sliderLayout->addWidget(_zone1);
    sliderLayout->addWidget(_zone2);
    sliderLayout->addWidget(_zone3);
    sliderLayout->addWidget(_zone4);
    sliderLayout->addWidget(_zone5);
    sliderLayout->addWidget(_zone6);
    sliderLayout->addSpacing(20);




    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("");

    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->addSpacing(5);
    centerLayout->addLayout(comboBoxLayout);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(sliderLayout);

    centerLayout->addStretch();
    centerLayout->setContentsMargins(0, 0, 0, 0);
    addCentralWidget(centralWidget, true, true, 0);

}
