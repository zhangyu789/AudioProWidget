#ifndef DANTELISTMODEL_H
#define DANTELISTMODEL_H

#include <QAbstractTableModel>

class DanteListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DanteListModel(QObject* parent = nullptr);
    ~DanteListModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QString getNameFromModelIndex(const QModelIndex& index) const;
    QString getTypeFromModelIndex(const QModelIndex& index) const;
private:
    QStringList _header;
    QList<QStringList> _dataList;
};

#endif // DanteListModel
