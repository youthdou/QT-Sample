#include "tablemodel.h"

TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_listData.clear();
    m_listHeaderNames.clear();

    m_listHeaderNames << "number" << "alphabet" << "string";

    const QString STR_ALPHABET = "abcdefghijklmnopqrstuvworz";

    for(int i = 0; i < 5; ++i)
    {
        QStringList listValues;
        listValues.append(QString::number(i));
        listValues.append(STR_ALPHABET.at(i));
        listValues.append(STR_ALPHABET.at(i) + QString::number(i));

        m_listData.append(listValues);
    }
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listData.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listData.at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    if(role == Qt::DisplayRole)
    {
        int iRow = index.row();
        int iCol = index.column();

        return m_listData.at(iRow).at(iCol);
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if(orientation != Qt::Horizontal)
    {
        return QVariant();
    }

    return m_listHeaderNames.at(section);
}

void TableModel::sort(int column, Qt::SortOrder order)
{
    emit layoutAboutToBeChanged();
    std::sort(m_listData.begin(), m_listData.end(), [this, column, order](QStringList data1, QStringList data2){
        bool bLessThan = data1.at(column) < data2.at(column);
        return order == Qt::AscendingOrder ? bLessThan : !bLessThan;
    });
    emit layoutChanged();
}

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{

}

bool MySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    return leftData.toString() < rightData.toString();
}
