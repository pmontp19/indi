#include "rellotge.h"
#include "ui_rellotge.h"

rellotge::rellotge(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::rellotge)
{
    ui->setupUi(this);
}

rellotge::~rellotge()
{
    delete ui;
}
