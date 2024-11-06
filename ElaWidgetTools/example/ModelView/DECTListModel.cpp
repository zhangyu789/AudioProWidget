#include "DECTListModel.h"

#include <QIcon>
DECTListModel::DECTListModel(QObject* parent)
    : QAbstractTableModel{parent}
{
    _header << "No."
            << "RX"
            << "Speaker Status"
            << "Signal Strength";
    // 初始化_dataList
    QStringList data0, data1, data2, data3, data4, data5, data6, data7, data8;
    data0 << "1" << "RX DECT 01" << "Online" << "99";
    data1 << "2" << "RX DECT 02" << "Online" << "99";
    data2 << "3" << "RX DECT 03" << "Online" << "99";
    data3 << "4" << "RX DECT 04" << "Online" << "99";
    data4 << "5" << "RX DECT 05" << "Online" << "78";
    data5 << "6" << "RX DECT 06" << "Online" << "59";
    data6 << "7" << "RX DECT 07" << "Online" << "59";
    data7 << "8" << "RX DECT 08" << "Online" << "68";
    data8 << "9" << "RX DECT 09" << "Online" << "43";
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

DECTListModel::~DECTListModel()
{
}

int DECTListModel::rowCount(const QModelIndex& parent) const
{
    return _dataList.count();
}

int DECTListModel::columnCount(const QModelIndex& parent) const
{
    return _header.count();
}

QVariant DECTListModel::data(const QModelIndex& index, int role) const
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

QVariant DECTListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return _header[section];
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}
