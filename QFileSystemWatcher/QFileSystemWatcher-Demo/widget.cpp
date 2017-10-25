#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>
#include <QMutexLocker>
#include <QCryptographicHash>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(&m_watcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(slotDirectoryChange(QString)));

    connect(&m_thread, SIGNAL(signalDirectoryChanged()),
            this, SLOT(slotThreadDirectoryChange()), Qt::QueuedConnection);
    m_thread.start();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
//    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
//                                                      ".",
//                                                      QFileDialog::ShowDirsOnly
//                                                      | QFileDialog::DontResolveSymlinks);
//    qDebug() << "[" << __FUNCTION__ << "]"
//             << dir;

//    m_watcher.addPath(dir);
//    m_thread.start();
}

void Widget::slotDirectoryChange(const QString &strPath)
{
    qDebug() << "[" << __FUNCTION__ << "]"
             << strPath;
    qDebug() << "[" << __FUNCTION__ << "]"
             << m_watcher.directories();
    m_watcher.addPath(strPath);
}

//void FileSystemWatcherThread::start()
//{
//    QMutexLocker locker(&m_mutex);
//    m_bRunning = true;
//}

void FileSystemWatcherThread::stop()
{
    QMutexLocker locker(&m_mutex);
    m_bRunning = false;
}

void FileSystemWatcherThread::addPath(const QString &strPath)
{
    QMutexLocker locker(&m_mutex);
    if(!m_listDirs.contains(strPath))
    {
        m_listDirs.append(strPath);
    }
}

QStringList FileSystemWatcherThread::getDirsAndFiles()
{
    QStringList listDirs = getDirs();

    QStringList listDirsAndFiles{};
    foreach(QString strDir, listDirs)
    {
        if(listDirsAndFiles.contains(strDir))
        {
            continue;
        }

        listDirsAndFiles.append(getDirsAndFiles(strDir));
    }

    qSort(listDirsAndFiles.begin(), listDirsAndFiles.end());

    return listDirsAndFiles;
}

void FileSystemWatcherThread::run()
{
    //qDebug() << "[" << __FUNCTION__ << "]" << QThread::currentThreadId();
    while(!isStop())
    {
        this->msleep(200);
        checkChangeOfDirectories();
        //qDebug() << "[" << __FUNCTION__ << "]" << QThread::currentThreadId();
    }
}

QStringList FileSystemWatcherThread::getDirs()
{
    QMutexLocker locker(&m_mutex);
    return m_listDirs;
}

void FileSystemWatcherThread::checkChangeOfDirectories()
{
//    QStringList listDirs = getDirs();

//    QStringList listDirsAndFiles{};
//    foreach(QString strDir, listDirs)
//    {
//        if(listDirsAndFiles.contains(strDir))
//        {
//            continue;
//        }

//        listDirsAndFiles.append(getDirsAndFiles(strDir));
//    }

//    qSort(listDirsAndFiles.begin(), listDirsAndFiles.end());

    QStringList listDirsAndFiles = getDirsAndFiles();
    //qDebug() << "[" << __FUNCTION__ << "]" << listDirsAndFiles;

    QString strMD5{};
    foreach(QString strFile, listDirsAndFiles)
    {
        strMD5 += strFile;
    }

    QByteArray ba{};
    ba.append(strMD5);
    strMD5 = QCryptographicHash::hash(ba, QCryptographicHash::Md5);

    if(strMD5 != m_strCurrentMD5)
    {
        emit signalDirectoryChanged();
        m_strCurrentMD5 = strMD5;
    }
}

QStringList FileSystemWatcherThread::getDirsAndFiles(const QString &strPath)
{
    QDir dir(strPath);
    if(!dir.exists())
    {
        return QStringList{};
    }

    QStringList listDirsAndFiles{};
    dir.setFilter(QDir::Dirs | QDir::Files);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList listFiles = dir.entryInfoList();

    foreach(QFileInfo fileInfo, listFiles)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
        {
            continue;
        }

        bool bDir = fileInfo.isDir();
        if(bDir)
        {
            foreach(auto strTempPath, getDirsAndFiles(fileInfo.filePath()))
            {
                if(listDirsAndFiles.contains(strTempPath))
                {
                    continue;
                }
                listDirsAndFiles.append(strTempPath);
            }
        }

        if(listDirsAndFiles.contains(fileInfo.absoluteFilePath()))
        {
            continue;
        }

        listDirsAndFiles.append(fileInfo.absoluteFilePath());
    }

    return listDirsAndFiles;
}

bool FileSystemWatcherThread::isStop()
{
    QMutexLocker locker(&m_mutex);
    return !m_bRunning;
}

void Widget::on_btnThreadWatcher_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                      ".",
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
    if(dir.isEmpty())
    {
        return;
    }
    qDebug() << "[" << __FUNCTION__ << "]"
             << dir;

    m_thread.addPath(dir + "/");
}

void Widget::slotThreadDirectoryChange()
{
    qDebug() << "[" << __FUNCTION__ << "]" << m_thread.getDirsAndFiles();
}
