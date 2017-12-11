#include "httpform.h"
#include "ui_httpform.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QFile>

HttpForm::HttpForm(QWidget *parent) :
    QWidget(parent),
    m_pManager(new QNetworkAccessManager(this)),
    ui(new Ui::HttpForm)
{
    ui->setupUi(this);
    connect(m_pManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotReplyFinished(QNetworkReply*)));
}

HttpForm::~HttpForm()
{
    delete ui;
}

void HttpForm::on_btnGet_clicked()
{
    QNetworkRequest request;
    request.setUrl(QUrl(ui->lineEdit->text()));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36");


     m_pManager->get(request);
//    QNetworkReply *pReply = m_pManager->get(request);
//    connect(pReply, SIGNAL(readyRead()),
//            this, SLOT(slotReadyRead()));
}

void HttpForm::slotReplyFinished(QNetworkReply *pReply)
{
    qDebug() << "[" << __FUNCTION__ << "]";
    if(pReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error happen";
    }

    ui->textBrowser->clear();
    QByteArray ba = pReply->readAll();
    //ui->textBrowser->setText(pReply->readAll());
    qDebug() << "Content: " ;
    //qDebug() << strContent;
    QFile file("test.txt");
    file.open(QIODevice::ReadWrite);
    file.write(ba);
    file.close();
    //ui->textBrowser->setText(strContent);
}

void HttpForm::slotReadyRead()
{
//    QNetworkReply *pReply = dynamic_cast<QNetworkReply *>(QObject::sender());

}
