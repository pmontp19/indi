#include "numerotext.h"
#include <QApplication>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    numerotext w;
    w.show();

    return a.exec();
}
