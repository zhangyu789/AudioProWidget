#include "RoutingWidget.h"
#include <ElaLineEdit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <ElaScrollPage.h>
RoutingWidget::RoutingWidget(QWidget *parent)
    : ElaScrollPage(parent), m_filterPartItem(std::make_shared<FilterPartItem>(nullptr))
{
    setTitleVisible(false);
    setContentsMargins(0, 0, 0, 0);
}

RoutingWidget::~RoutingWidget()
{
}

ReceiverModelData::ReceiverModelData(QObject *parent) : QAbstractItemModel(parent) {}

ReceiverModelData::~ReceiverModelData() {}

QModelIndex ReceiverModelData::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QModelIndex ReceiverModelData::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

int ReceiverModelData::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int ReceiverModelData::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant ReceiverModelData::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

bool ReceiverModelData::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

Qt::ItemFlags ReceiverModelData::flags(const QModelIndex &index) const
{
    return Qt::ItemFlags();
}

QVariant ReceiverModelData::headerData(int section, Qt::Orientation orientation,
                                       int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        int leftCount = 4;
        return QString("Receiver%1").arg(leftCount);
    }
    else if (orientation == Qt::Vertical && role == Qt::DisplayRole)
    {
        int rightCount = 5;
        return QString("Receiver%1").arg(rightCount);
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}
