#include "suma_1_2.h"
#include "ui_suma_1_2.h"

suma_1_2::suma_1_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::suma_1_2)
{
    ui->setupUi(this);
}

suma_1_2::~suma_1_2()
{
    delete ui;
}
