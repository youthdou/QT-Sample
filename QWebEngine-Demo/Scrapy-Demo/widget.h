#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QWebEngineView>
#include <QWebEnginePage>

#include "spider.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void signalHtml(const QString &);

private slots:
    void on_btnLoad_clicked();
    void on_btnReload_clicked();
    void slotSearchFinished(bool bOk);
    void slotParseHtml(const QString &);
    void on_runBtn_clicked();
    void slotLoadProgress(int progress);
    void handleCookieAdded(const QNetworkCookie &cookie);
    void handleCookieDeleted(const QNetworkCookie &cookie);
    void on_btnCrawl_clicked();
    void onFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature);


private:
    void search(const QString &strCompanyName);

private:
    Ui::Widget *ui;
    QWebEngineView *m_pWebView;
    //QWebEnginePage *m_pWebPage;
    Spider spider;
    QList<QNetworkCookie> m_listCookies;

    QWebEngineProfile *m_profile;
};

#endif // WIDGET_H
