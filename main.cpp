#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    qInstallMessageHandler([](QtMsgType type, const QMessageLogContext &context, const QString &msg) {
        QFile outFile("debug_log.txt");
        if(outFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
            QTextStream ts(&outFile);
            ts << msg << Qt::endl;
        }
    });

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
