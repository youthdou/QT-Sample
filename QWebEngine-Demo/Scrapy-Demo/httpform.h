#ifndef HTTPFORM_H
#define HTTPFORM_H

#include <QWidget>

class QNetworkAccessManager;
class QNetworkReply;

namespace Ui {
class HttpForm;
}

class HttpForm : public QWidget
{
    Q_OBJECT

public:
    explicit HttpForm(QWidget *parent = 0);
    ~HttpForm();

private slots:
    void on_btnGet_clicked();
    void slotReplyFinished(QNetworkReply *pReply);
    void slotReadyRead();

private:
    Ui::HttpForm *ui;

    QNetworkAccessManager *m_pManager;
};

#endif // HTTPFORM_H
