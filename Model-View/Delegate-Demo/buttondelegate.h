#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include<QItemDelegate>
class ButtonDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ButtonDelegate();

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    ~ButtonDelegate();
};

#endif // BUTTONDELEGATE_H
