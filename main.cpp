#include <QDebug>
#include <QObject>
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QClipboard>
#include <QtNetwork>

#include "utils.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QClipboard *clipboard = QApplication::clipboard();
    QString clip_text = clipboard->text();

    DumpzService service;
    service.postDump(clip_text);

    return app.exec();
}
