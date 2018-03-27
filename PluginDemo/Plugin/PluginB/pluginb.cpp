#include "pluginb.h"


PluginB::PluginB(QObject *parent) :
    QObject(parent)
{
}

QString PluginB::name()
{
    return "PluginB";
}
