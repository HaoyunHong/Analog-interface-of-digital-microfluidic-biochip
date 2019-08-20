#include "mymainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myMainWindow w;
    w.show();

    return a.exec();
}
