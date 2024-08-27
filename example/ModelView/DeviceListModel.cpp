#include "DeviceListModel.h"

#include <QIcon>
DeviceListModel::DeviceListModel(QObject* parent)
    : QAbstractTableModel{parent}
{
    _header << "Device Name"
            << "Product Type"
            << "Sample Rate"
            << "Encoding"
            << "Product Version"
            << "Dante Version"
            << "Primary Address"
            << "Operate";
    // 初始化_dataList
    QStringList data0, data1, data2, data3, data4, data5, data6, data7, data8;
    data0 << "Dante1" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.0.7" << "Edit";
    data1 << "Dante2" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.67.99" << "Edit";
    data2 << "Dante3" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.34.45" << "Edit";
    data3 << "Dante4" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.12.23" << "Edit";
    data4 << "Dante5" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.23.76" << "Edit";
    data5 << "Dante6" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.75.72" << "Edit";
    data6 << "Dante7" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.0.12" << "Edit";
    data7 << "Dante8" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.66.76" << "Edit";
    data8 << "Dante9" << "TX 2" << "44.1k" << "PCM 24" << "101" << "4.2.2.3" << "192.168.32.57" << "Edit";
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

DeviceListModel::~DeviceListModel()
{
}

int DeviceListModel::rowCount(const QModelIndex& parent) const
{
    return _dataList.count();
}

int DeviceListModel::columnCount(const QModelIndex& parent) const
{
    return _header.count();
}

QVariant DeviceListModel::data(const QModelIndex& index, int role) const
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

QVariant DeviceListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return _header[section];
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}