﻿#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QVector>

class GroupWidget : public QWidget {
    Q_OBJECT
public:
    explicit GroupWidget(QWidget *parent = nullptr);

    void addGroup(const QString& groupName);                   // 添加 Group
    void addTx2(const QString& txName, const QString& groupName);  // 添加 TX2 到指定 Group
    void addZone(const QString& zoneName, const QString& txName, const QString& groupName); // 添加 Zone 到指定的 TX2

private:
    QVBoxLayout* _mainLayout;
    QMap<QString, QGroupBox*> _groups;                   // 存储每个 Group 的 QGroupBox
    QMap<QString, QHBoxLayout*> _txListLayouts;          // 存储每个 Group 的 TX2 区域布局
    QMap<QString, QVBoxLayout*> _zoneListLayouts;        // 存储每个 Group 的 Zone 区域布局
    QMap<QString, QVector<QPushButton*>> _zoneButtons;   // 存储每个 TX2 下的 Zone 按钮
    QMap<QString, QLabel*> _txLabels;                    // 存储每个 TX2 的 Zone 列表标题
};

#endif // GROUPWIDGET_H
