#include "plugina.h"


PluginA::PluginA(QObject *parent) :
    QObject(parent)
{
}

QString PluginA::name()
{
    return "PluginA";
}
