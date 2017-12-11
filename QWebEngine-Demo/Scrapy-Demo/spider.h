#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QNetworkAccessManager>

class Spider : public QObject
{
    Q_OBJECT
public:
    Spider(QObject *parent = nullptr);
    //void load(const QString &strUrl);
    void crawl(const QVariant &varCookie);

private slots:
    void slotLoadFinished(QNetworkReply *pReply);

private:
    QNetworkAccessManager m_manager;
};

#endif // SPIDER_H
