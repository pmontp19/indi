#include "mylabel.h"
#include <iostream>


MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
    r = g = b = 255;
}

void MyLabel::setIniColor(int r, int g, int b) {
    this->r = r;
    this->g = g;
    this->b = b;
    updateColor();
    emit sendR(r);
    emit sendG(g);
    emit sendB(b);
}

void MyLabel::updateColor() {
    QPalette pal = palette();
    QColor nouColor;
    nouColor.setRgb(r, g, b, 255);
    pal.setColor(QPalette::Background, nouColor);
    setPalette(pal);
    emit changeColor(r, g, b);
}

void MyLabel::setRed(int r) {
    this->r = r;
    updateColor();
}

void MyLabel::setGreen(int g) {
    this->g = g;
    updateColor();
}

void MyLabel::setBlue(int b) {
    this->b = b;
    updateColor();
}
