#ifndef DECTLISTMODEL_H
#define DECTLISTMODEL_H

#include <QAbstractTableModel>

class DECTListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DECTListModel(QObject* parent = nullptr);
    ~DECTListModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QStringList _header;
    QList<QStringList> _dataList;
};

#endif // DECTLISTMODEL_H
