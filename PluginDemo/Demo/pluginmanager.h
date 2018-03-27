#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QHash>

#include "../plugin/plugininterface.h"

class PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager *instance();
    PluginInterface *plugin(const QString &strName);

    QStringList pluginNames();

signals:

public slots:

private:
    explicit PluginManager(QObject *parent = 0);
    void loadPlugin();

private:
    QHash<QString, PluginInterface *> m_hashPlugins;

};

#endif // PLUGINMANAGER_H
