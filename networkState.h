#ifndef NETWORKSTATE_H
#define NETWORKSTATE_H

#include <QtCore>
#include <QtNetwork>

class NetworkState
{
private:
    bool networkState;

public:
    NetworkState()
    {
        networkState = false;
    }

    bool getNetworkState()
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest networkRequest = QNetworkRequest(QUrl("http://www.baidu.com"));
        QNetworkReply *reply = manager->get(networkRequest);
        QEventLoop eventLoop;
        QObject::connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
        eventLoop.exec();
        QString dataPacket = reply->readAll();
        QRegExp rx("baidu");
        if(rx.indexIn(dataPacket) > -1)
            networkState = true;
        else
            networkState = false;
        return networkState;
    }
};

#endif // NETWORKSTATE_H
