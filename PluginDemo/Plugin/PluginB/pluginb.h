#ifndef PLUGINB_H
#define PLUGINB_H

#include <QtPlugin>
#include <QObject>

#include "../plugininterface.h"


class PluginB : public QObject, PluginInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.zqy.PluginInterface" FILE "PluginB.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)

public:
    PluginB(QObject *parent = 0);
    ~PluginB()
    {

    }

    virtual QString name() Q_DECL_OVERRIDE;
};

#endif // PLUGINA_H
