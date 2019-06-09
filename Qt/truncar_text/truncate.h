#ifndef TRUNCATE_H
#define TRUNCATE_H

#include <QMainWindow>

namespace Ui {
class truncate;
}

class truncate : public QMainWindow
{
    Q_OBJECT

public:
    explicit truncate(QWidget *parent = nullptr);
    ~truncate();

private:
    Ui::truncate *ui;
};

#endif // TRUNCATE_H
