#ifndef ALARMA_H
#define ALARMA_H

#include <QMainWindow>

namespace Ui {
class alarma;
}

class alarma : public QMainWindow
{
    Q_OBJECT

public:
    explicit alarma(QWidget *parent = 0);
    ~alarma();

private:
    Ui::alarma *ui;
};

#endif // ALARMA_H
