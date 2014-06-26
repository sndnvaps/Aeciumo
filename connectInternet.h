#ifndef CONNECTINTERNET_H
#define CONNECTINTERNET_H

#include "networkState.h"
#include <QtCore>
//#include <QtWidgets>
#include <QWidget>

class ConnectInternet : public QThread
{
    Q_OBJECT

private:
    NetworkState *networkState;
    QProcess *process;
    QStringList argumentList;

private slots:
    void outputProcessMessage();

public:
    ConnectInternet(QString id, QString password, QString hostIP, QString nci);
    ~ConnectInternet();
    void run();
    QString initLib();
};

#endif // CONNECTINTERNET_H
