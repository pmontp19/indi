#include "slider_color.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    slider_color w;
    w.show();

    return a.exec();
}
