#include "spider.h"

#include <QDebug>

#include <QNetworkRequest>
#include <QNetworkReply>

#include <QFile>

Spider::Spider(QObject *parent) :
    QObject(parent)
{
    connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slotLoadFinished(QNetworkReply*)));
}

void Spider::crawl(const QVariant &varCookie)
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://www.qichacha.com/search?key=%E6%99%BA%E5%99%A8%E4%BA%91"));
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36");

    if(varCookie.isValid())
    {
        request.setHeader(QNetworkRequest::CookieHeader, varCookie);
    }

    m_manager.get(request);
}

void Spider::slotLoadFinished(QNetworkReply *pReply)
{
    qDebug() << "[" << __FUNCTION__ << "]";
    if(pReply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error happen";
    }

    QByteArray ba = pReply->readAll();
    //ui->textBrowser->setText(pReply->readAll());
    qDebug() << "Content: " ;
    //qDebug() << strContent;
    QFile file("test.html");
    file.open(QIODevice::ReadWrite);
    file.write(ba);
    file.close();
}


