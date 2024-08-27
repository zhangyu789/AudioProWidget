#include "NetworkStatusModel.h"

#include <QIcon>
NetworkStatusModel::NetworkStatusModel(QObject* parent)
    : QAbstractTableModel{parent}
{
    _header << "Device Name"
            << "Primary Status"
            << "Primary TX B/W"
            << "Primary RX B/W";
    // 初始化_dataList
    QStringList data0, data1, data2, data3, data4, data5, data6, data7, data8;
    data0 << "Dante1" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    data1 << "Dante2" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    data2 << "Dante3" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    data3 << "Dante4" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    data4 << "Dante5" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    data5 << "Dante6" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    data6 << "Dante7" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    data7 << "Dante8" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    data8 << "Dante9" << "1Gbps" << "<1 Mbps" << "<1 Mbps";
    _dataList.append(data0);
    _dataList.append(data1);
    _dataList.append(data2);
    _dataList.append(data3);
    _dataList.append(data4);
    _dataList.append(data5);
    _dataList.append(data6);
    _dataList.append(data7);
    _dataList.append(data8);

}

NetworkStatusModel::~NetworkStatusModel()
{
}

int NetworkStatusModel::rowCount(const QModelIndex& parent) const
{
    return _dataList.count();
}

int NetworkStatusModel::columnCount(const QModelIndex& parent) const
{
    return _header.count();
}

QVariant NetworkStatusModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        // 对于所有列，包括第一列，都返回相应的数据
        return _dataList[index.row()][index.column()];
    }
    else if (role == Qt::DecorationPropertyRole)
    {
        return Qt::AlignCenter;
    }
    return QVariant();
}

QVariant NetworkStatusModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return _header[section];
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}
