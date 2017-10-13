#include "widget.h"
#include "ui_widget.h"

#include <QTimer>

#include <QDebug>

const QString  STR_BUTTON_FINISH_STYLE = "background-color: #2f68bc; color:white; border:0px solid #0d5bce;";
const QString  STR_BUTTON_PROGRESS_STYLE = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #2f68bc, stop:%1 #2f68bc, stop:%2 #999999, stop:1 #999999);"
                                           "color:white;border:0px solid #2f68bc;";
const QString  STR_BUTTON_START_STYLE = "background-color: #999999; color:white;border:0px solid #0d5bce;";

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_iCounter(0),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()),
            this, SLOT(slotTimeOut()));

    ui->pushButton->setStyleSheet(STR_BUTTON_START_STYLE);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    m_iCounter = 0;
    m_pTimer->start(200);
}

void Widget::slotTimeOut()
{
    const int MAX_COUNT = 50;
    if(m_iCounter >= MAX_COUNT)
    {
        ui->pushButton->setStyleSheet(STR_BUTTON_FINISH_STYLE);
        m_pTimer->stop();
        return;
    }

    double dRatio = (double)m_iCounter++ / MAX_COUNT;

    QString strStyleSheet = STR_BUTTON_PROGRESS_STYLE.arg(QString::number(dRatio - 0.001)).arg(QString::number(dRatio));
    qDebug() << "[" << __FUNCTION__ << "]"
             << strStyleSheet;
    ui->pushButton->setStyleSheet(strStyleSheet);
}
