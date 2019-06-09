#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = nullptr);

signals:
    void enviaText(const QString &);
public slots:
    void tractaReturn();
};

#endif // MYLINEEDIT_H
