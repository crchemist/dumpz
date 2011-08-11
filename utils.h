#ifndef UTILS_H
#define UTILS_H

#include <QDebug>
#include <QObject>
#include <QClipboard>
#include <QtNetwork>
#include <QCoreApplication>
#include <QApplication>

class DumpzService: public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;

public:
    DumpzService()
    {
       manager = new QNetworkAccessManager();
    }

    QString postDump(QString text)
    {
        QString url;
        QByteArray data;
        QUrl params;

        QNetworkRequest request(QUrl("http://dumpz.org/"));

        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        params.addQueryItem("lexer", "text");
        params.addQueryItem("code", text);
        data.append(params.toString());
        data.remove(0, 1);

        reply = manager->post(request, data);
        connect(reply, SIGNAL(finished()), this, SLOT(responseReceived()));

        return url;
    };


public slots:
    void responseReceived()
    {
        qDebug() << reply->error();
        QApplication::quit();
    }
};

#endif