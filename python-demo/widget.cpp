#include "widget.h"
#include "ui_widget.h"

#include "Python.h"

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnRun_clicked()
{
    Py_Initialize();
    PyRun_SimpleString("print('Hello world!')\nprint('Hello world')");
    Py_Finalize();
}

void Widget::on_btnRunFun_clicked()
{
    int res;

    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString("print(sys.path)");
    PyObject *pModule = nullptr, *pFunc = nullptr;
    PyObject *pArgs, *pValue;
    pModule = PyImport_ImportModule("great_module");
    if(nullptr == pModule)
    {
        qDebug() << "[" << __FUNCTION__ << "]" << "Get module failed!";
        return;
    }

    pFunc = PyObject_GetAttrString(pModule, "great_function");

    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, PyLong_FromLong(ui->spinBox->value()));

    //pValue = PyObject_CallObject(pFunc, pArgs);
    pValue = PyEval_CallObject(pFunc, pArgs);

    res = PyLong_AsLong(pValue);
    Py_Finalize();

    ui->label->setText(QString::number(res));
    qDebug() << "[" << __FUNCTION__ << "]" << res;

}

void Widget::on_btnCrawl_clicked()
{
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyRun_SimpleString("print(sys.path)");
    PyObject *pModule = nullptr, *pFunc = nullptr;
    PyObject *pArgs, *pValue;
    pModule = PyImport_ImportModule("crawl");
    if(nullptr == pModule)
    {
        qDebug() << "[" << __FUNCTION__ << "]" << "Get module failed!";
        return;
    }

    pFunc = PyObject_GetAttrString(pModule, "parseIP");

    pArgs = PyTuple_New(1);
    QByteArray ba = ui->lineEdit->text().toLocal8Bit();
    PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(ba.data()));

    //pValue = PyObject_CallObject(pFunc, pArgs);
    pValue = PyEval_CallObject(pFunc, pArgs);

    //res = PyUnicode_AsUnicode(pValue);
    //char str[100];
    char *p;
    PyArg_Parse(pValue, "s", &p);
    Py_Finalize();

    ui->label->setText(QString::fromUtf8(p));
    qDebug() << "[" << __FUNCTION__ << "]" << p;
}
