#ifndef SIGNALSTRENGTHMODEL_H
#define SIGNALSTRENGTHMODEL_H

#include <QAbstractTableModel>

class SignalStrengthModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SignalStrengthModel(QObject* parent = nullptr);
    ~SignalStrengthModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QStringList _header;
    QList<QStringList> _dataList;
};

#endif // SignalStrengthModel
