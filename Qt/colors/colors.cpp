#include "colors.h"
#include "ui_colors.h"

colors::colors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::colors)
{
    ui->setupUi(this);
}

colors::~colors()
{
    delete ui;
}
