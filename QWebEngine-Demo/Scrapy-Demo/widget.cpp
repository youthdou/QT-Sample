#include "widget.h"
#include "ui_widget.h"

//#include "spider.h"

#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineCookieStore>
#include <QFile>
#include <QWebEngineProfile>
#include <QTimer>

#include "featurepermissionbar.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    m_pWebView(new QWebEngineView(this)),
    m_listCookies{},
    m_profile(QWebEngineProfile::defaultProfile()),
    //m_pWebPage(new QWebEnginePage()),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->gridLayout->replaceWidget(ui->widget, m_pWebView);
    ui->widget->hide();

    //m_pWebView->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, false);
    //m_pWebView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

    QWebEngineCookieStore *pStore = m_pWebView->page()->profile()->cookieStore();
    connect(pStore, &QWebEngineCookieStore::cookieAdded, this, &Widget::handleCookieAdded);
    connect(pStore, &QWebEngineCookieStore::cookieRemoved, this, &Widget::handleCookieDeleted);
    connect(this, SIGNAL(signalHtml(const QString &)),
            this, SLOT(slotParseHtml(const QString &)));
    connect(m_pWebView, SIGNAL(loadFinished(bool)),
            this, SLOT(slotSearchFinished(bool)));
    connect(m_pWebView, SIGNAL(loadProgress(int)),
            this, SLOT(slotLoadProgress(int)));

    connect(m_pWebView, &QWebEngineView::renderProcessTerminated,
            [=](QWebEnginePage::RenderProcessTerminationStatus termStatus, int statusCode) {
        const char *status = "";
        switch (termStatus) {
        case QWebEnginePage::NormalTerminationStatus:
            status = "(normal exit)";
            break;
        case QWebEnginePage::AbnormalTerminationStatus:
            status = "(abnormal exit)";
            break;
        case QWebEnginePage::CrashedTerminationStatus:
            status = "(crashed)";
            break;
        case QWebEnginePage::KilledTerminationStatus:
            status = "(killed)";
            break;
        }

        qInfo() << "Render process exited with code" << statusCode << status;
        QTimer::singleShot(0, [=] {m_pWebView->reload(); });
    });
    //m_pWebPage->load(QUrl("https://www.qichacha.com/"));
//m_pWebPage->load(QUrl("http://blog.csdn.net/li235456789/article/details/50959384"));

}

Widget::~Widget()
{
    //delete m_pWebView;
//    delete m_pWebPage;
    delete ui;
}

void Widget::on_btnLoad_clicked()
{
    QString strUrl = ui->lineEdit->text();
    if(!strUrl.startsWith("http"))
    {
        strUrl = "https://" + strUrl;
    }

    QWebEnginePage *pWebPage = new QWebEnginePage(m_profile, m_pWebView);
    pWebPage->load(strUrl);
    m_pWebView->setPage(pWebPage);
    connect(m_pWebView->page(), &QWebEnginePage::featurePermissionRequested,
            this, &Widget::onFeaturePermissionRequested);

//    m_pWebView->load(strUrl);
//    m_pWebPage->toHtml([this](const QString &v ) mutable {
//        qDebug() << "print html";
//        qDebug() << v;
//    });
}

void Widget::on_btnReload_clicked()
{
    m_pWebView->reload();
}

void Widget::slotSearchFinished(bool bOk)
{
    if(bOk)
    {
        qDebug() << "Load successful!";
    }
    else
    {
        qDebug() << "Load Failed!";
    }

//    m_pWebView->page()->toHtml([this](const QString &strHtml) mutable
//    {
//        emit signalHtml(strHtml);
//        //QString html = str;
//        //qDebug() << html;
//    });
//    m_pWebView->page()->toPlainText([](const QString &strHtml) mutable {qDebug() << strHtml;});
//    m_pWebView->page()->toHtml( [&](const QString &v ){
//        qDebug() << v;
//    });
    m_pWebView->page();
    //on_runBtn_clicked();
}

void Widget::slotParseHtml(const QString &strHtml)
{
    qDebug() << "[" << __FUNCTION__ << "]";
    qDebug() << strHtml;
}

void Widget::search(const QString &strCompanyName)
{

}

void Widget::on_runBtn_clicked()
{
    QFile file("function.js");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Read js file error!";
    }
    QString strJS = file.readAll();
    //qDebug() << "JS File: " << strJS;
//    m_pWebView->page()->runJavaScript("function myFunction() {var myvar = document.getElementById('V3_Search_bt').value; return myvar;} myFunction();",
//                                      [] (const QVariant &result) {
//                                      qDebug()<<result;
//                                      });
    m_pWebView->page()->runJavaScript(strJS, [] (const QVariant &result) {
                                             qDebug() << result;
                                              });
//    m_pWebView->page()->runJavaScript("document.getElementsByClassName('ma_h1')[0].href");
    //    m_pWebView->page()->runJavaScript("alert('this is web alert'); ");
}

void Widget::slotLoadProgress(int progress)
{
    qDebug() << "[" << progress << "]";
}

void Widget::handleCookieAdded(const QNetworkCookie &cookie)
{
    qDebug() << "[" << __FUNCTION__ << "]";
    m_listCookies.append(cookie);
}

void Widget::handleCookieDeleted(const QNetworkCookie &cookie)
{
    m_listCookies.removeAll(cookie);
}

void Widget::on_btnCrawl_clicked()
{
    QByteArray ba{"UM_distinctid=15fc9618e3fb60-0247280f81bcbf-c303767-1fa400-15fc9618e4095b; _uab_collina=151091215440978226171676; acw_tc=AQAAAB+9/3Fl/QUAQnxBMcPSKR9eOiuR; hasShow=1; zg_did=%7B%22did%22%3A%20%2215fc9618f1e2ef-05d8de423d6c96-c303767-1fa400-15fc9618f1feb0%22%7D; CNZZDATA1254842228=1177572670-1510910194-https%253A%252F%252Fwww.google.co.uk%252F%7C1512116945; _umdata=535523100CBE37C31119C49925621DA4CAD5AC49D5728F21FF68A49AA2C477018616571F0FB8226DCD43AD3E795C914C0D931B5C570D7CF691C5367E352E9494; zg_de1d1a35bfa24ce29bbf2c7eb17e6c4f=%7B%22sid%22%3A%201512121495960%2C%22updated%22%3A%201512121509185%2C%22info%22%3A%201511519835274%2C%22superProperty%22%3A%20%22%7B%7D%22%2C%22platform%22%3A%20%22%7B%7D%22%2C%22utm%22%3A%20%22%7B%7D%22%2C%22referrerDomain%22%3A%20%22www.qichacha.com%22%2C%22cuid%22%3A%20%22826b343f0e605f9f9d3f3df661c811c0%22%7D; PHPSESSID=561hres430auv8f9hbb54t7mm4"};
    QList<QNetworkCookie> listCookies = QNetworkCookie::parseCookies(ba);
    qDebug() << "[" << __FUNCTION__ << "]" << listCookies.size();

    QVariant var;
    if(listCookies.size() > 0)
    {
        var.setValue(listCookies);
    }
    spider.crawl(var);
}

void Widget::onFeaturePermissionRequested(const QUrl &securityOrigin, QWebEnginePage::Feature feature)
{
    FeaturePermissionBar *permissionBar = new FeaturePermissionBar(this);
    connect(permissionBar, &FeaturePermissionBar::featurePermissionProvided,
            m_pWebView->page(), &QWebEnginePage::setFeaturePermission);

    // Discard the bar on new loads (if we navigate away or reload).
    connect(m_pWebView->page(), &QWebEnginePage::loadStarted, permissionBar, &QObject::deleteLater);

    permissionBar->requestPermission(securityOrigin, feature);
}
