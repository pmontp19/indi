#ifndef CANVICOLOR_H
#define CANVICOLOR_H

#include <QMainWindow>

namespace Ui {
class CanviColor;
}

class CanviColor : public QMainWindow
{
    Q_OBJECT

public:
    explicit CanviColor(QWidget *parent = nullptr);
    ~CanviColor();

private:
    Ui::CanviColor *ui;
};

#endif // CANVICOLOR_H
