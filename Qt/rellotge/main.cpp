#include "rellotge.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rellotge w;
    w.show();

    return a.exec();
}
