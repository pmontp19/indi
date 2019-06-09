#ifndef SLIDER_COLOR_H
#define SLIDER_COLOR_H

#include <QMainWindow>

namespace Ui {
class slider_color;
}

class slider_color : public QMainWindow
{
    Q_OBJECT

public:
    explicit slider_color(QWidget *parent = nullptr);
    ~slider_color();

private slots:
    void on_pushButton_clicked();

private:
    Ui::slider_color *ui;
};

#endif // SLIDER_COLOR_H
