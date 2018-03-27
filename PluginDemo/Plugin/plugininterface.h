#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QString>

//! [0]
class PluginInterface
{
public:
    PluginInterface() {}
    virtual ~PluginInterface() {}
    virtual QString name() = 0;
};


QT_BEGIN_NAMESPACE

#define PluginInterface_iid "org.qt-project.zqy.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
QT_END_NAMESPACE

#endif // PLUGININTERFACE_H
