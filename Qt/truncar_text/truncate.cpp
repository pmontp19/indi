#include "truncate.h"
#include "ui_truncate.h"

truncate::truncate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::truncate)
{
    ui->setupUi(this);
}

truncate::~truncate()
{
    delete ui;
}
