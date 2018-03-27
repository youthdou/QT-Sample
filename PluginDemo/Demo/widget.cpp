#include "widget.h"
#include "ui_widget.h"

#include "pluginmanager.h"
#include "../plugin/plugininterface.h"

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

void Widget::on_btnLoad_clicked()
{
    ui->comboBox->clear();
    ui->comboBox->addItems(PluginManager::instance()->pluginNames());
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        return;
    }
    PluginInterface *pInterface = PluginManager::instance()->plugin(arg1);
    ui->label->setText(pInterface->name());
}
