#include "truncate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    truncate w;
    w.show();

    return a.exec();
}
