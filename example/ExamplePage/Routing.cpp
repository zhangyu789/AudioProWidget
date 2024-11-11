#include "Routing.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
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

    // 创建一个水平布局来容纳过滤器部分和矩阵表格
    QHBoxLayout *mainContentLayout = new QHBoxLayout;
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
}

QGroupBox* Routing::createFilterGroup() {
    // 创建过滤器组
    QGroupBox *filterGroup = new QGroupBox("Filter");
    QVBoxLayout *filterLayout = new QVBoxLayout;

    // 添加 Transmitter 和 Receivers 复选框
    QCheckBox *transmitterCheckBox = new QCheckBox("Transmitter");
    QCheckBox *receiversCheckBox = new QCheckBox("Receivers");
    filterLayout->addWidget(transmitterCheckBox);
    filterLayout->addWidget(receiversCheckBox);

    filterGroup->setLayout(filterLayout);
    return filterGroup;
}

QTableWidget* Routing::createMatrixTable() {
    int parentCount = 4;  // 父级数量，例如 Dante1 到 Dante4
    int childrenPerParent = 10;  // 每个父级下的子级数量

    int rows = parentCount * (childrenPerParent + 1);  // 包含父级和子级行
    int columns = parentCount * (childrenPerParent + 1);  // 包含父级和子级列
    QTableWidget *table = new QTableWidget(rows, columns);

    // 用于跟踪每个父级是否被展开的状态
    QVector<bool> parentExpanded(parentCount, true);

    int currentRow = 0, currentColumn = 0;
    int childCellSize = 40;  // 设置子级单元格大小，使其成为正方形

    // 遍历每个父级
    for (int p = 0; p < parentCount; ++p) {
        QString parentLabel = QString("Dante%1").arg(p + 1);

        // 创建父级行/列的标签
        QTableWidgetItem* verticalParentItem = new QTableWidgetItem(parentLabel);
        table->setVerticalHeaderItem(currentRow, verticalParentItem);

        QTableWidgetItem* horizontalParentItem = new QTableWidgetItem(parentLabel);
        table->setHorizontalHeaderItem(currentColumn, horizontalParentItem);

        // 设置每个父级的子级标签
        for (int r = 1; r <= childrenPerParent; ++r) {
            QString childLabelRow = QString("%1").arg(r, 2, 10, QChar('0'));
            table->setVerticalHeaderItem(currentRow + r, new QTableWidgetItem(childLabelRow));

            for (int c = 1; c <= childrenPerParent; ++c) {
                QString childLabelColumn = QString("%1").arg(c, 2, 10, QChar('0'));
                if (r == 1) {
                    // 设置水平表头项（仅在第一行时设置，避免重复）
                    table->setHorizontalHeaderItem(currentColumn + c, new QTableWidgetItem(childLabelColumn));
                }

                // 设置复选框
                QTableWidgetItem *item = new QTableWidgetItem("");
                item->setCheckState(Qt::Unchecked);
                table->setItem(currentRow + r, currentColumn + c, item);

                // 设置子级单元格大小为正方形
                table->setRowHeight(currentRow + r, childCellSize);
                table->setColumnWidth(currentColumn + c, childCellSize);
            }
        }

        // 设置父级行和列的高度和宽度不同于子级，使其视觉上更明显
        table->setRowHeight(currentRow, childCellSize);  // 父级行高度
        table->setColumnWidth(currentColumn, childCellSize);  // 父级列宽度

        // 隐藏父级单元格的交互
        QTableWidgetItem *parentItem = new QTableWidgetItem("");
        parentItem->setFlags(Qt::NoItemFlags);
        table->setItem(currentRow, currentColumn, parentItem);

        // 连接父级标签的点击事件，控制子级显示/隐藏
        connect(table->verticalHeader(), &QHeaderView::sectionClicked, this, [=, &parentExpanded]() mutable {
            if (parentExpanded[p]) {
                for (int i = 1; i <= childrenPerParent; ++i) {
                    table->hideRow(currentRow + i);
                }
            } else {
                for (int i = 1; i <= childrenPerParent; ++i) {
                    table->showRow(currentRow + i);
                }
            }
            parentExpanded[p] = !parentExpanded[p];
        });
        connect(table->horizontalHeader(), &QHeaderView::sectionClicked, this, [=, &parentExpanded]() mutable {
            if (parentExpanded[p]) {
                for (int i = 1; i <= childrenPerParent; ++i) {
                    table->hideColumn(currentColumn + i);
                }
            } else {
                for (int i = 1; i <= childrenPerParent; ++i) {
                    table->showColumn(currentColumn + i);
                }
            }
            parentExpanded[p] = !parentExpanded[p];
        });

        // 更新当前行和列索引
        currentRow += childrenPerParent + 1;
        currentColumn += childrenPerParent + 1;
    }

    // 为每个父类的子类交叉单元格添加复选框
    for (int pr = 0; pr < parentCount; ++pr) {
        int rowBase = pr * (childrenPerParent + 1) + 1;  // 子级行的起始位置

        for (int pc = 0; pc < parentCount; ++pc) {
            int colBase = pc * (childrenPerParent + 1) + 1;  // 子级列的起始位置

            for (int r = 0; r < childrenPerParent; ++r) {
                for (int c = 0; c < childrenPerParent; ++c) {
                    // 设置每个父级的每个子级行与所有父级的每个子级列交叉位置的复选框
                    QTableWidgetItem *item = new QTableWidgetItem("");
                    item->setCheckState(Qt::Unchecked);
                    table->setItem(rowBase + r, colBase + c, item);
                }
            }
        }
    }

    return table;
}
