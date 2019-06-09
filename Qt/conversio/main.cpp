#include "conversio.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    conversio w;
    w.show();

    return a.exec();
}
