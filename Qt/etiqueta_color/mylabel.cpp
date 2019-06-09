#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

void MyLabel::changeToRed() {
    setStyleSheet("background-color: rgb(255,0,0);");
}

void MyLabel::changeToBlue() {
    setStyleSheet("background-color: rgb(0,0,255);");
}

