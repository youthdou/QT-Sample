#include "widget.h"
#include "ui_widget.h"
#include <QListView>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->comboBox->setView(new QListView());
}

Widget::~Widget()
{
    delete ui;
}
