#include "Routing.h"
#include "Device.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <ElaCheckBox.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QGroupBox>
#include <QHeaderView>

Routing::Routing(QWidget* parent)
    : ElaScrollPage(parent)
{
    setTitleVisible(false);
    setAttribute(Qt::WA_DontCreateNativeAncestors);

    // 创建中心部件并设置窗口标题为空
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("");

    QVBoxLayout* centerLayout = new QVBoxLayout(centralWidget);

    // 初始化过滤器部分
    filterGroupBox = createFilterGroup();

    // 初始化矩阵表格
    matrixTable = createMatrixTable();
    matrixTable->setShowGrid(false);  // 隐藏网格线

    // 使用样式表仅隐藏内部的网格线，而保留外边框
    matrixTable->setStyleSheet("QTableWidget {border: 0px solid black;}");

    // 设置水平表头高度
    matrixTable->horizontalHeader()->setStyleSheet("QHeaderView::section { height: 50px; }");

    // 设置整个表格控件的固定高度
    // matrixTable->setFixedHeight(800); // 设置高度为400，可根据需要调整

    matrixTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // 禁止所有列调整大小
    matrixTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    // 禁止所有行调整大小
    matrixTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    // 根据内容计算表格高度并设置
    adjustTableHeight(matrixTable);
    // 创建一个水平布局来容纳过滤器部分和矩阵表格
    QVBoxLayout *mainContentLayout = new QVBoxLayout;
    mainContentLayout->addWidget(filterGroupBox);
    mainContentLayout->addWidget(matrixTable);

    // 将主内容布局添加到中心布局中
    centerLayout->addLayout(mainContentLayout);

    // 添加拉伸因子以使内容充满整个布局
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->setSpacing(0);
    centerLayout->addStretch();

    // 将中心部件添加到 ElaScrollPage
    addCentralWidget(centralWidget, true, true, 0);


    // 创建 Dante1 设备对象
    QList<QString> dante1Subclasses = {"01", "02", "03"};
    Device dante1("Dante1", "Receiver", dante1Subclasses);

    // 创建 Dante2 设备对象
    QList<QString> dante2Subclasses = {"01", "02", "03", "04"};
    Device dante2("Dante2", "Transmitter", dante2Subclasses);

    // 创建设备列表，存放 Dante1 和 Dante2
    QList<Device> devices;
    devices.append(dante1);
    devices.append(dante2);


}
void Routing::adjustTableHeight(QTableWidget* table) {
    int totalHeight = 0;

    // 计算每一行的高度
    for (int row = 0; row < table->rowCount(); ++row) {
        totalHeight += table->rowHeight(row);
    }

    // 加上表头的高度
    totalHeight += table->horizontalHeader()->height();

    // 加上表格的边框或其他额外空间的高度
    int extraHeight = 4;  // 额外高度，用于边框或间隙，可以根据需要调整
    totalHeight += extraHeight;

    // 设置表格控件的高度
    table->setFixedHeight(totalHeight + 10);
}
QGroupBox* Routing::createFilterGroup() {
    // 创建过滤器组
    QGroupBox *filterGroup = new QGroupBox("Filter");
    QVBoxLayout *filterLayout = new QVBoxLayout;

    // 添加 Transmitter 和 Receivers 复选框
    ElaCheckBox *transmitterCheckBox = new ElaCheckBox("Transmitter");
    ElaCheckBox *receiversCheckBox = new ElaCheckBox("Receivers");
    filterLayout->addWidget(transmitterCheckBox);
    filterLayout->addWidget(receiversCheckBox);

    filterGroup->setLayout(filterLayout);
    return filterGroup;
}

QTableWidget* Routing::createMatrixTable() {
    int parentCountRows = 8;  // 父级行数量，例如 Dante1 到 Dante4
    int childrenPerParentRows = 5;  // 每个父级行下的子级数量

    int parentCountColumns = 5;  // 父级列数量，例如 Dante1 到 Dante4
    int childrenPerParentColumns = 5;  // 每个父级列下的子级数量

    // 计算总的行和列数
    int rows = parentCountRows * (childrenPerParentRows + 1);  // 包含父级和子级行
    int columns = parentCountColumns * (childrenPerParentColumns + 1);  // 包含父级和子级列
    QTableWidget *table = new QTableWidget(rows, columns);

    // 用于跟踪每个父级是否被展开的状态
    pParentExpandedRows = new QMap<int, bool>;  // 改为使用 QMap
    pParentExpandedColumns = new QMap<int, bool>;  // 改为使用 QMap

    int currentRow = 0, currentColumn = 0;
    int childCellSize = 10;  // 设置子级单元格大小

    // 遍历每个父级
    for (int p = 0; p < parentCountRows; ++p) {
        (*pParentExpandedRows)[p] = true;
        QString parentLabel = QString("Receiver%1").arg(p + 1);

        // 创建父级行的标签
        QTableWidgetItem* verticalParentItem = new QTableWidgetItem(parentLabel);
        table->setVerticalHeaderItem(currentRow, verticalParentItem);

        // 设置每个父级行的子级行标签
        for (int r = 1; r <= childrenPerParentRows; ++r) {
            QString childLabelRow = QString("%1").arg(r, 2, 10, QChar('0'));
            table->setVerticalHeaderItem(currentRow + r, new QTableWidgetItem(childLabelRow));
            table->setRowHeight(currentRow + r, childCellSize);
        }

        // 设置父级行高度
        table->resizeRowToContents(currentRow);
        // 连接父类行的双击事件，控制每个父类的子类行显示/隐藏
        connect(table->verticalHeader(), &QHeaderView::sectionDoubleClicked, this, [=](int index) {
            // 输出调试信息，确认信号触发
            qDebug() << "Double-clicked on vertical header at index:" << index;
            // 计算父类行的索引
            int parentIndex = index / (childrenPerParentRows + 1);

            // 确保双击的是父类行
            if (index % (childrenPerParentRows + 1) == 0) {
                bool isExpanded = (*pParentExpandedRows).value(parentIndex, true);

                int rowBase = parentIndex * (childrenPerParentRows + 1);

                if (isExpanded) {
                    for (int i = 1; i <= childrenPerParentRows; ++i) {
                        table->hideRow(rowBase + i);
                        qDebug() << "hideRow:" << rowBase + i;
                    }
                } else {
                    for (int i = 1; i <= childrenPerParentRows; ++i) {
                        table->showRow(rowBase + i);
                        qDebug() << "showRow:" << rowBase + i;
                    }
                }

                (*pParentExpandedRows)[parentIndex] = !isExpanded;

            }
        });

        // 更新当前行索引
        currentRow += childrenPerParentRows + 1;

    }
    for (int p = 0; p < parentCountColumns; ++p) {
        (*pParentExpandedColumns)[p] = true;
        QString parentLabel = QString("Transmitter%1").arg(p + 1);

        // 创建父级列的标签
        QTableWidgetItem* horizontalParentItem = new QTableWidgetItem(parentLabel);
        table->setHorizontalHeaderItem(currentColumn, horizontalParentItem);

        // 设置每个父级的子级列标签
        for (int c = 1; c <= childrenPerParentColumns; ++c) {
            QString childLabelColumn = QString("%1").arg(c, 2, 10, QChar('0'));
            table->setHorizontalHeaderItem(currentColumn + c, new QTableWidgetItem(childLabelColumn));
            table->setColumnWidth(currentColumn + c, childCellSize);
        }

        // 设置父级列的高度
        table->resizeColumnToContents(currentColumn);

        // 连接父类列的双击事件，控制每个父类的子类列显示/隐藏
        connect(table->horizontalHeader(), &QHeaderView::sectionDoubleClicked, this, [=](int index) {
            // 输出调试信息，确认信号触发
            qDebug() << "Double-clicked on horizontal header at index:" << index;
            // 计算父类列的索引
            int parentIndex = index / (childrenPerParentColumns + 1);

            // 确保双击的是父类列
            if (index % (childrenPerParentColumns + 1) == 0) {
                bool isExpanded = (*pParentExpandedColumns).value(parentIndex, true);

                int colBase = parentIndex * (childrenPerParentColumns + 1);

                if (isExpanded) {
                    for (int i = 1; i <= childrenPerParentColumns; ++i) {
                        table->hideColumn(colBase + i);
                        qDebug() << "hideColumn:" << colBase + i;
                    }
                } else {
                    for (int i = 1; i <= childrenPerParentColumns; ++i) {
                        table->showColumn(colBase + i);
                        qDebug() << "showColumn:" << colBase + i;
                    }
                }

                (*pParentExpandedColumns)[parentIndex] = !isExpanded;
            }
        });


        // 更新当前列索引
        currentColumn += childrenPerParentColumns + 1;

    }
    // 为每个父类的子类交叉单元格添加复选框
    for (int pr = 0; pr < parentCountRows; ++pr) {
        int rowBase = pr * (childrenPerParentRows + 1) + 1;  // 子级行的起始位置

        for (int pc = 0; pc < parentCountColumns; ++pc) {
            int colBase = pc * (childrenPerParentColumns + 1) + 1;  // 子级列的起始位置

            for (int r = 0; r < childrenPerParentRows; ++r) {
                for (int c = 0; c < childrenPerParentColumns; ++c) {
                    // 设置每个父级的每个子级行与所有父级的每个子级列交叉位置的复选框
                    QTableWidgetItem *item = new QTableWidgetItem("");
                    item->setCheckState(Qt::Unchecked);
                    table->setItem(rowBase + r, colBase + c, item);
                }
            }
        }
    }

    // 遍历父类行和列，禁用指定的单元格
    for (int pr = 0; pr < parentCountRows; ++pr) {
        int rowBase = pr * (childrenPerParentRows + 1);  // 父类行的起始位置
        for (int pc = 0; pc < parentCountColumns; ++pc) {
            int colBase = pc * (childrenPerParentColumns + 1);  // 父类列的起始位置

            // 1. 禁用父类行和父类列的交叉单元格
            QTableWidgetItem *parentItem = table->item(rowBase, colBase);
            if (!parentItem) {
                parentItem = new QTableWidgetItem();
                table->setItem(rowBase, colBase, parentItem);
            }
            parentItem->setFlags(Qt::NoItemFlags);

            // 2. 禁用父类行和子类列的交叉单元格
            for (int c = 1; c <= childrenPerParentColumns; ++c) {
                QTableWidgetItem *childColumnItem = table->item(rowBase, colBase + c);
                if (!childColumnItem) {
                    childColumnItem = new QTableWidgetItem();
                    table->setItem(rowBase, colBase + c, childColumnItem);
                }
                childColumnItem->setFlags(Qt::NoItemFlags);
            }

            // 3. 禁用子类行和父类列的交叉单元格
            for (int r = 1; r <= childrenPerParentRows; ++r) {
                QTableWidgetItem *childRowItem = table->item(rowBase + r, colBase);
                if (!childRowItem) {
                    childRowItem = new QTableWidgetItem();
                    table->setItem(rowBase + r, colBase, childRowItem);
                }
                childRowItem->setFlags(Qt::NoItemFlags);
            }
        }
    }

    return table;
}
