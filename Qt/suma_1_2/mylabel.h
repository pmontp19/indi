#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

signals:

public slots:
    void setZero();
    void addOne();
    void addTwo();
};

#endif // MYLABEL_H
