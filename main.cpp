#include <QDebug>
#include <QObject>
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QClipboard>
#include <QtNetwork>

class DumpzService: public QObject {
    Q_OBJECT

    public:
        DumpzService();

        QString postDump(QString data);
};

QString DumpzService::postDump(QString data) {
    QString url;
    QByteArray data;
    QUrl params;

    QNetworkAccessManager *manager;
    QNetworkRequest request(QUrl("http://dumpz.org/"));

    manager = new QNetworkAccessManager();
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    params.addQueryItem("lexer", "text");
    params.addQueryItem("code", clip_text);
    data.append(params.toString());
    data.remove(0, 1);

    QNetworkReply *reply = manager->post(request, data);

    qDebug() << reply->bytesAvailable();

    return url;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QClipboard *clipboard = QApplication::clipboard();
    QString clip_text = clipboard->text();

    return app.exec();
}
