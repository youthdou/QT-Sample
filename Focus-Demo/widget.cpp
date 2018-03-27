#include "widget.h"
#include "ui_widget.h"

#include "inputwidget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //ui->lineEdit->setFocus();

    InputWidget *pWidget = new InputWidget();
    //ui->gridLayout->addWidget(pWidget);
    //pWidget->setFocus();

    QHBoxLayout *pLayout = new QHBoxLayout();
    pLayout->addWidget(pWidget);
    ui->widget->setLayout(pLayout);
    //pWidget->setFocus();
}

Widget::~Widget()
{
    delete ui;
}
