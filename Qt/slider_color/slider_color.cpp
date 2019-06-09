#include "slider_color.h"
#include "ui_slider_color.h"

slider_color::slider_color(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::slider_color)
{
    ui->setupUi(this);
}

slider_color::~slider_color()
{
    delete ui;
}

void slider_color::on_pushButton_clicked()
{
    int R = int(ui->lcdNumber->value());
    int G = int(ui->lcdNumber_2->value());
    int B = int(ui->lcdNumber_3->value());
    QString str = "background-color:";
    QColor col (R,G,B);
    str += col.name();
    ui->label->setStyleSheet(str);
}
