#ifndef NETWORKSTATUSMODEL_H
#define NETWORKSTATUSMODEL_H

#include <QAbstractTableModel>

class NetworkStatusModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit NetworkStatusModel(QObject* parent = nullptr);
    ~NetworkStatusModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QStringList _header;
    QList<QStringList> _dataList;
};

#endif // NetworkStatusModel
