#ifndef ROUTING_H
#define ROUTING_H

#include "ElaScrollPage.h"
#include <QGroupBox>
#include <QTableWidget>
#include <QMap>  // 用于存储父级是否展开的状态

class QWebEngineView;
class ElaComboBox;
class ElaSlider;

class Routing : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit Routing(QWidget* parent = nullptr);

private:
    // 新增私有成员变量，用于过滤器和矩阵表格
    QGroupBox* filterGroupBox{nullptr};        // 过滤器框
    QTableWidget* matrixTable{nullptr};        // 矩阵表格

    // 新增变量用于存储父级展开状态
    QMap<int, bool>* pParentExpandedRows{nullptr};   // 存储父级行是否展开的状态
    QMap<int, bool>* pParentExpandedColumns{nullptr}; // 存储父级列是否展开的状态

    // 调整表格高度使其适应内容行数的函数
    void adjustTableHeight(QTableWidget* table);

    // 用于初始化过滤器和矩阵表格的方法
    QGroupBox* createFilterGroup();
    QTableWidget* createMatrixTable(); // 创建矩阵表格

Q_SIGNALS:

};

#endif // ROUTING_H
