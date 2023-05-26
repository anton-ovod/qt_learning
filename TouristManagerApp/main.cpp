#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile stylesheetsfile(":/stylesheets/MacOS.qss");
    stylesheetsfile.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(stylesheetsfile.readAll());
    a.setStyleSheet(stylesheet);
    MainWindow w;
    w.show();
    return a.exec();
}
