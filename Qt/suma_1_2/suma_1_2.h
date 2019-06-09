#ifndef SUMA_1_2_H
#define SUMA_1_2_H

#include <QMainWindow>

namespace Ui {
class suma_1_2;
}

class suma_1_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit suma_1_2(QWidget *parent = nullptr);
    ~suma_1_2();

private:
    Ui::suma_1_2 *ui;
};

#endif // SUMA_1_2_H
