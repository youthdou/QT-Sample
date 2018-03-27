#include "inputwidget.h"
#include "ui_inputwidget.h"

#include <QDebug>

InputWidget::InputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputWidget)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
}

InputWidget::~InputWidget()
{
    delete ui;
}

void InputWidget::focusInEvent(QFocusEvent *pEvent)
{
    qDebug() << "Focus in";
    ui->lineEdit->setFocus();
    QWidget::focusInEvent(pEvent);
}
