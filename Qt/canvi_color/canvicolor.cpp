#include "canvicolor.h"
#include "ui_canvicolor.h"

CanviColor::CanviColor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CanviColor)
{
    ui->setupUi(this);
}

CanviColor::~CanviColor()
{
    delete ui;
}
