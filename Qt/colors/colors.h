#ifndef COLORS_H
#define COLORS_H

#include <QMainWindow>

namespace Ui {
class colors;
}

class colors : public QMainWindow
{
    Q_OBJECT

public:
    explicit colors(QWidget *parent = nullptr);
    ~colors();

private:
    Ui::colors *ui;
};

#endif // COLORS_H
