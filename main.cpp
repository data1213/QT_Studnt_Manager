#include "addstudents.h"
#include <QApplication>
#include "MainWindow.h" //包含头

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /***********/
    MainWindow w;
    w.show();

    return a.exec();
}
