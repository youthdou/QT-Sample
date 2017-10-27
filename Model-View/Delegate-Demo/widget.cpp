#include "widget.h"
#include "ui_widget.h"

#include <QStandardItemModel>
#include "buttondelegate.h"
#include <QPushButton>

#include "tableviewdelegate.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    initView();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initView()
{
    this->m_pStandardItemModel = new QStandardItemModel();
    this->m_pStandardItemModel->setColumnCount(4);
    this->m_pStandardItemModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("歌曲名"));
    this->m_pStandardItemModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("操作"));
    this->m_pStandardItemModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("歌手"));
    this->m_pStandardItemModel->setHeaderData(3, Qt::Horizontal, QStringLiteral("时长"));
    this->ui->tableView->setModel(this->m_pStandardItemModel);

    ///
    this->m_pStandardItemModel->setItem(0, 0, new QStandardItem(QStringLiteral("可惜没如果")));
    this->m_pStandardItemModel->setItem(0, 1, new QStandardItem(QStringLiteral("播放")));
    this->m_pStandardItemModel->setItem(0, 2, new QStandardItem(QStringLiteral("林俊杰")));
    this->m_pStandardItemModel->setItem(0, 3, new QStandardItem(QStringLiteral("4:16")));

    this->m_pStandardItemModel->setItem(1, 0, new QStandardItem(QStringLiteral("可惜没如果")));
    this->m_pStandardItemModel->setItem(1, 1, new QStandardItem(QStringLiteral("播放")));
    this->m_pStandardItemModel->setItem(1, 2, new QStandardItem(QStringLiteral("林俊杰")));
    this->m_pStandardItemModel->setItem(1, 3, new QStandardItem("4:16"));
    //
    //this->ui->tableView->setItemDelegateForColumn(2, new ButtonDelegate());
    this->ui->tableView->setItemDelegate(new TableViewDelegate(this));

    this->ui->tableView->setIndexWidget(this->ui->tableView->indexAt(QPoint(0, 0)), new QPushButton("xx"));
}
