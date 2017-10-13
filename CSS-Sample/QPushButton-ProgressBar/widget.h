#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void slotTimeOut();

private:
    Ui::Widget *ui;
    QTimer *m_pTimer;

    int m_iCounter;
};

#endif // WIDGET_H
