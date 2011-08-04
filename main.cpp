#include <QDebug>
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QClipboard>
#include <QtNetwork>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QByteArray data;
    QUrl params;

    QNetworkAccessManager *manager;
    QNetworkRequest request(QUrl("http://dumpz.org/"));

    manager = new QNetworkAccessManager();
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QClipboard *clipboard = QApplication::clipboard();
    QString clip_text = clipboard->text();

    params.addQueryItem("lexer", "text");
    params.addQueryItem("code", clip_text);
    data.append(params.toString());
    data.remove(0, 1);

    QNetworkReply *reply = manager->post(request, data);


    qDebug() << reply->bytesAvailable();


    return 0;
}
