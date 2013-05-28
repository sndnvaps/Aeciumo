#ifndef QSSREADER_H
#define QSSREADER_H

#include <QtCore>

class QssReader
{
private:
    QString qssData;

public:
    QssReader(QString qssPath)
    {
        QFile *qssFile = new QFile(qssPath);
        if(qssFile->open(QIODevice::ReadOnly))
        {
            QTextStream *textStream = new QTextStream(qssFile);
            while (!textStream->atEnd())
            {
                qssData.append(textStream->readLine());
            }
        }
    }

    QString getQssData()
    {
        return qssData;
    }
};

#endif // QSSREADER_H
