#include "widget.h"
#include "httpform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

//    HttpForm w;
//    w.show();

    return a.exec();
}
