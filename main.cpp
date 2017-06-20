#include "mainwindow.h"
#include "calcthread.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CalcThread ct;

    qRegisterMetaType<CoordinatesList>();

    w.setWindowTitle("Лабораторная работа 3");
    w.show();

    QObject::connect(&w, SIGNAL(SendDataToStart(int, int, int, int)), &ct, SLOT(GetDataToStart(int, int, int, int)));
    QObject::connect(&w, SIGNAL(StartCalc()), &ct, SLOT(start()));
    QObject::connect(&ct, SIGNAL(UpdateData(CoordinatesList)), &w, SLOT(UpdateData(CoordinatesList)));
    QObject::connect(&ct, SIGNAL(GraphIsOk()), &w, SLOT(GraphIsOk()));

    return a.exec();
}
