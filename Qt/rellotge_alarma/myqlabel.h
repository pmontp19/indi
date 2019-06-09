#ifndef MYQLABEL_H
#define MYQLABEL_H

#include <QLabel>

class MyQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyQLabel(QWidget *parent = 0);

private:
    QString hour,minute;
    bool is_set;

signals:
    void enviaZero(const int &);
    void radioOff2On(const bool &);

public slots:
    void setOn();
    void setOff();
    void setHour(int h);
    void setMinute(int m);
    void update();
    void reset();
};

#endif // MYQLABEL_H
