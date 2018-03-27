#include "widget.h"
#include "ui_widget.h"

#include "TestConnectionPoolWithMultiThread.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_testMultiThread_clicked()
{
    for (int i = 0; i < 10; ++i)
    {
        TestConnectionPoolWithMultiThread *thread = new TestConnectionPoolWithMultiThread(i);
        thread->start();
        // QThread::msleep(50);
    }

}
