#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QStandardItemModel;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void initView();

private:
    Ui::Widget *ui;
    QStandardItemModel *m_pStandardItemModel;
};

#endif // WIDGET_H
