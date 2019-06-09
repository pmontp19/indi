#ifndef RELLOTGE_H
#define RELLOTGE_H

#include <QMainWindow>

namespace Ui {
class rellotge;
}

class rellotge : public QMainWindow
{
    Q_OBJECT

public:
    explicit rellotge(QWidget *parent = nullptr);
    ~rellotge();

private:
    Ui::rellotge *ui;
};

#endif // RELLOTGE_H
