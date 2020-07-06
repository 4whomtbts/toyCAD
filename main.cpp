#include "mycad.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mycad w;
    w.show();
    return a.exec();
}
