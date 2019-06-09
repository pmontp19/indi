#include "myqlabel.h"

MyQLabel::MyQLabel(QWidget *parent) : QLabel(parent)
{
    hour = minute = "00";
    is_set = false;
}

void MyQLabel::setOn() {
    is_set = true;
    setStyleSheet("background-color: green;\ncolor: rgb(255, 255, 255);");
    update();
}
void MyQLabel::setOff(){
    is_set = false;
    setStyleSheet("background-color: red;\ncolor: rgb(255, 255, 255);");
    setText("Alarma desactivada");
}

void MyQLabel::setHour(int h) {
    if (h < 10) {
        hour = QString("0") + QString::number(h);
    } else {
        hour = QString::number(h);
    }
    if (is_set) update();
}
void MyQLabel::setMinute(int m) {
    if (m < 10) {
        minute = QString("0") + QString::number(m);
    } else {
        minute = QString::number(m);
    }
    if (is_set) update();
}

void MyQLabel::update() {
    QString str = QString("Alarma -- %1:%2").arg(hour).arg(minute);
    setText(str);
}

void MyQLabel::reset() {
    setOff();
    emit enviaZero(0);
    emit radioOff2On(true);
}
