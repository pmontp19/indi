#include "mylcd.h"

MyLCD::MyLCD(QWidget *parent) : QLCDNumber(parent)
{

}

void MyLCD::setTextColor(int number) {
    display(number);
    if (number == 0) {
        setStyleSheet("color:green;");
    }
    else if (number %2 == 0) {
        setStyleSheet("color:blue;");
    }
    else if (number %2 == 1) {
        setStyleSheet("color:red;");
    }
}

void MyLCD::setZero() {
    setTextColor(0);
}
