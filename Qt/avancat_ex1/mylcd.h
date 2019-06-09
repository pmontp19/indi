#ifndef MYLCD_H
#define MYLCD_H

#include <QLCDNumber>

class MyLCD : public QLCDNumber
{
    Q_OBJECT
public:
    explicit MyLCD(QWidget *parent = nullptr);

signals:

public slots:
    void setTextColor(int number);
    void setZero();
};
#endif // MYLCD_H
