#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

class TableModel : public QAbstractTableModel
{
public:
    TableModel(QObject *parent = Q_NULLPTR);

    virtual int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;

    virtual QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;


    virtual void sort(int column, Qt::SortOrder order) Q_DECL_OVERRIDE;
private:
    QStringList m_listHeaderNames;
    QList<QStringList> m_listData;
};


class MySortFilterProxyModel : public QSortFilterProxyModel
{
public:
    MySortFilterProxyModel(QObject *parent = Q_NULLPTR);
    virtual bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;
};

#endif // TABLEMODEL_H
