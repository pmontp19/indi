#include "colors.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    colors w;
    w.show();

    return a.exec();
}
