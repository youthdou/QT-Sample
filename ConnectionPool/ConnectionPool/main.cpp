#include "widget.h"
#include <QApplication>

#include "connectionpool.h"

#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = ConnectionPool::openConnection();
    ConnectionPool::closeConnection(db);
    Widget w;
    w.show();

    return a.exec();
}
