#include "main_win.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication myApp(argc, argv);
    MainWindow myWin;
    myWin.show();

    return myApp.exec();
}
