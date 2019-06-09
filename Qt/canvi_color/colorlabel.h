#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>

class ColorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ColorLabel(QWidget *parent = nullptr);

private:
    int counter;

signals:

public slots:
    void setColorCanvi();
};

#endif // COLORLABEL_H
