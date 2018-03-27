#ifndef PLUGINA_H
#define PLUGINA_H

#include <QtPlugin>
#include <QObject>

#include "../plugininterface.h"


class PluginA : public QObject, PluginInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.zqy.PluginInterface" FILE "PluginA.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)

public:
    PluginA(QObject *parent = 0);
    ~PluginA()
    {

    }

    virtual QString name() Q_DECL_OVERRIDE;
};

#endif // PLUGINA_H
