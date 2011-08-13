#ifndef UTILS_H
#define UTILS_H

#include <iostream>

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
        params.addQueryItem("code", QUrl::toPercentEncoding(text));

        data.append(params.toString());
        data.remove(0, 1);

        reply = manager->post(request, data);
        connect(reply, SIGNAL(finished()), this, SLOT(responseReceived()));

        return url;
    };


public slots:
    void responseReceived()
    {
        QByteArray location = reply->rawHeader("Location");

        // put url to terminal
        std::cout << ((QString) location).toStdString();

        // put url to clipboard
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText((QString) location);

        QApplication::quit();
    }
};

#endif
