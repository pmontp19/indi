#include "alarma.h"
#include "ui_alarma.h"

alarma::alarma(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::alarma)
{
    ui->setupUi(this);
}

alarma::~alarma()
{
    delete ui;
}
