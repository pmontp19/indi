#include "colorlabel.h"

ColorLabel::ColorLabel(QWidget *parent) : QLabel(parent)
{
    counter = 0;
}

void ColorLabel::setColorCanvi() {
    if (counter == 0) {
        setStyleSheet("background-color:yellow");
        counter++;
    } else if (counter == 1) {
        setStyleSheet("background-color:green");
        counter++;
    } else if (counter == 2) {
    setStyleSheet("background-color:red ");
    counter = 0;
    }
}
