#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc < 3)
    {
        return 1;
    }
    QString vfsPath = QString::fromLocal8Bit(argv[1]);
    QString startupScriptPath = QString::fromLocal8Bit(argv[2]);
    MainWindow w(vfsPath,startupScriptPath);
    w.show();
    return QApplication::exec();
}
