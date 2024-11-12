#ifndef ROUTING_H
#define ROUTING_H

#include "ElaScrollPage.h"
#include <QGroupBox>
#include <QTableWidget>

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
    QGroupBox* filterGroupBox{nullptr};
    QTableWidget* matrixTable{nullptr};
    // 调整表格高度使其适应内容行数的函数
    void adjustTableHeight(QTableWidget* table);
    // 用于初始化过滤器和矩阵表格的方法
    QGroupBox* createFilterGroup();
    QTableWidget* createMatrixTable();

Q_SIGNALS:

};

#endif // ROUTING_H
