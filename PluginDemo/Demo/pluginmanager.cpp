#include "pluginmanager.h"

#include <QCoreApplication>
#include <QPluginLoader>
#include <QDir>

#include <QDebug>

PluginManager *PluginManager::instance()
{
    static PluginManager s_pluginMgr;

    return &s_pluginMgr;
}

PluginInterface *PluginManager::plugin(const QString &strName)
{
    return m_hashPlugins.value(strName, Q_NULLPTR);
}

QStringList PluginManager::pluginNames()
{
    return m_hashPlugins.keys();
}

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{
    loadPlugin();
}

void PluginManager::loadPlugin()
{
    QDir pluginsDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug"
            || pluginsDir.dirName().toLower() == "release")
    {
        pluginsDir.cdUp();
    }
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS")
    {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    pluginsDir.cd("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        if(!fileName.endsWith(".dll"))
        {
            continue;
        }
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        qDebug() << "version: " << pluginLoader.metaData().value("MetaData").toObject().value("version").toString();;
        QObject *plugin = pluginLoader.instance();
        if(plugin == Q_NULLPTR)
        {
            continue;
        }

        PluginInterface *pInterface = qobject_cast<PluginInterface *>(plugin);
        if(pInterface == Q_NULLPTR)
        {
            continue;
        }

        m_hashPlugins.insert(pInterface->name(), pInterface);
    }
}
