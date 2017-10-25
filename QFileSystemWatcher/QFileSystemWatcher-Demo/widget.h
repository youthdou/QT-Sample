#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QFileSystemWatcher>

#include <QThread>
#include <QMutex>

namespace Ui {
class Widget;
}

class FileSystemWatcherThread : public QThread
{
    Q_OBJECT
public:
    FileSystemWatcherThread() :
        m_bRunning(true)
    {

    }

    ~FileSystemWatcherThread()
    {
        stop();
        wait();
    }

    //void start();
    void stop();
    void addPath(const QString &strPath);
    QStringList getDirsAndFiles();

signals:
    void signalDirectoryChanged();

protected:
    virtual void run();

private:
    QStringList getDirs();
    void checkChangeOfDirectories();
    QStringList getDirsAndFiles(const QString &strPath);
    bool isStop();

private:
    bool m_bRunning;
    QStringList m_listDirs;
    QString m_strCurrentMD5;

    QMutex m_mutex;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void slotDirectoryChange(const QString &);
    void on_btnThreadWatcher_clicked();
    void slotThreadDirectoryChange();

private:
    void addDirectoryToWatcher();

private:
    Ui::Widget *ui;

    QFileSystemWatcher m_watcher;

    FileSystemWatcherThread m_thread;
};

#endif // WIDGET_H
