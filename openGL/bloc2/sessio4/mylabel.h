#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

signals:
    void changeColor(int r, int g, int b);
    void sendR(int color);
    void sendG(int color);
    void sendB(int color);

public slots:
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
    void setIniColor(int r, int g, int b);

private:
    void updateColor();
    int r,g,b;

};

#endif // MYLABEL_H
