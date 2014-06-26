#include "connectInternet.h"
#include <QApplication>

ConnectInternet::ConnectInternet(QString id, QString password, QString hostIP, QString nci)
{
    networkState = new NetworkState();
    process = new QProcess(this);
    connect(process, SIGNAL(readyRead()), this, SLOT(outputProcessMessage()));
    argumentList.append("-u");
    argumentList.append(id);
    argumentList.append("-p");
    argumentList.append(password);
    argumentList.append("-h");
    argumentList.append(hostIP);
    argumentList.append("-d");
    argumentList.append(nci);
}

ConnectInternet::~ConnectInternet()
{
    delete networkState;
    delete process;
}

void ConnectInternet::run()
{
    if(!networkState->getNetworkState())
    {
        process->execute(initLib(), argumentList);
        // qDebug() << "CONNECT INTERNET THREAD";
    }
}

QString ConnectInternet::initLib()
{
    QString path_app = QApplication::applicationDirPath();
    QString path_lib = path_app + "/baslib";
    QString path_config = "/home/moky/.baslib";
    QFile *file_lib = new QFile(path_lib);
    if(!file_lib->exists())
        QFile::copy(":/lib/baslib", path_lib);
    QFile *file_config = new QFile(path_config);
    if(!file_config->exists())
        QFile::copy(":/lib/.baslib", path_config);
    return path_lib;
}

void ConnectInternet::outputProcessMessage()
{
    qDebug() << "READALL";
    qDebug() << process->readAll();
}
