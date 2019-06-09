#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

void MyLabel::setZero() {
    setText(QChar('0'));
}
void MyLabel::addOne() {
    int current = text().toInt();
    current = current + 1;
    QString str = QString::number(current);
    setText(str);
}
void MyLabel::addTwo() {
    int current = text().toInt();
    current = current + 2;
    QString str = QString::number(current);
    setText(str);
}
