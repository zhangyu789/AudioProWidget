#ifndef ROUTINGWIDGET_H
#define ROUTINGWIDGET_H
#include <ElaLineEdit.h>
#include <iostream>
#include <memory>
#include <ElaScrollPage.h>
#include <QLabel>
#include <ElaLineEdit.h>
#include <ElaTreeView.h>
#include "CustomTreeVIewRotatedItemDelegate.h"
// pre declare

// Filter and two search edit
struct FilterPartItem
{
    FilterPartItem(QWidget *parent = nullptr)
    {
        m_label = std::make_shared<QLabel>(parent);
        m_label->setFixedSize(100, 30);
        m_label->setText("Filter");

        m_searchEdit1 = std::make_shared<ElaLineEdit>(parent);
        m_searchEdit1->setFixedSize(100, 30);
        m_searchEdit1->setPlaceholderText("Search");

        m_searchEdit2 = std::make_shared<ElaLineEdit>(parent);
        m_searchEdit2->setFixedSize(100, 30);
        m_searchEdit2->setPlaceholderText("Search");
    };

private:
    std::shared_ptr<QLabel> m_label = nullptr;
    std::shared_ptr<ElaLineEdit> m_searchEdit1 = nullptr;
    std::shared_ptr<ElaLineEdit> m_searchEdit2 = nullptr;
};

// Receiver TreeView modelData
struct ReceiverModelData : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ReceiverModelData(QObject *parent = nullptr);
    ~ReceiverModelData();
    // virtual functions
    QModelIndex parent(const QModelIndex &child) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

// Receiver TreeView widget
struct ReceiversItem
{

    ReceiversItem(QWidget *parent = nullptr)
    {
        m_leftTreeView = std::make_shared<ElaTreeView>(parent);
        m_leftTreeView->setModel(new ReceiverModelData(parent));

        m_topTreeView = std::make_shared<ElaTreeView>(parent);
        m_topTreeView->setModel(new ReceiverModelData(parent));
        RotatedItemDelegate *delegate = new RotatedItemDelegate(m_topTreeView.get());
        m_topTreeView->setItemDelegate(delegate);
    };

private:
    std::shared_ptr<ElaTreeView> m_leftTreeView = nullptr;
    std::shared_ptr<ElaTreeView> m_topTreeView = nullptr;
};

// Routing page widget
class RoutingWidget : public ElaScrollPage
{
    // Q_OBJECT
public:
    explicit RoutingWidget(QWidget *parent = nullptr);
    ~RoutingWidget();

private:
    std::shared_ptr<FilterPartItem> m_filterPartItem = nullptr;
};

#endif // ROUTINGWIDGET_H