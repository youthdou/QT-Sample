#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class TableModel;
class MySortFilterProxyModel;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    TableModel *m_pModel;

    MySortFilterProxyModel *m_pSortModel;
};

#endif // WIDGET_H
