#include "alarma.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    alarma w;
    w.show();

    return a.exec();
}
