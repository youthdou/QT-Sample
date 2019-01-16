#include "widget.h"
#include "ui_widget.h"

#include "tablemodel.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pModel = new TableModel(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_pSortModel = new MySortFilterProxyModel(this);
    m_pSortModel->setSourceModel(m_pModel);

    ui->tableView->setModel(m_pModel);
    ui->tableView_2->setModel(m_pSortModel);
}

Widget::~Widget()
{
    delete ui;
}
