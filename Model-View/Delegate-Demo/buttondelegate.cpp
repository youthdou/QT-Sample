#include "buttondelegate.h"
#include <QPushButton>

ButtonDelegate::ButtonDelegate()
{

}

QWidget *ButtonDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QPushButton * btn = new QPushButton("delegate", parent);
    return btn;
}

void ButtonDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void ButtonDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void ButtonDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

ButtonDelegate::~ButtonDelegate()
{

}
