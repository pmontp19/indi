#ifndef NUMEROTEXT_H
#define NUMEROTEXT_H

#include <QMainWindow>

namespace Ui {
class numerotext;
}

class numerotext : public QMainWindow
{
    Q_OBJECT

public:
    explicit numerotext(QWidget *parent = nullptr);
    ~numerotext();

private:
    Ui::numerotext *ui;
};

#endif // NUMEROTEXT_H
