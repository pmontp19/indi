#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

void MyLabel::truncateText(int val) {
    QString str = text();
    str.truncate(val);
    setText(str);
}
