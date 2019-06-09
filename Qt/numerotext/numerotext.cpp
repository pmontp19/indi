#include "numerotext.h"
#include "ui_numerotext.h"

numerotext::numerotext(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::numerotext)
{
    ui->setupUi(this);
}

numerotext::~numerotext()
{
    delete ui;
}
