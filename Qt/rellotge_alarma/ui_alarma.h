/********************************************************************************
** Form generated from reading UI file 'alarma.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALARMA_H
#define UI_ALARMA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDial>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "myqlabel.h"

QT_BEGIN_NAMESPACE

class Ui_alarma
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLCDNumber *hores;
    QLCDNumber *minuts;
    QDial *dialON;
    QDial *dialOFF;
    QRadioButton *radioOn;
    QRadioButton *radioOff;
    QPushButton *resetButton;
    MyQLabel *labelEstat;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *alarma)
    {
        if (alarma->objectName().isEmpty())
            alarma->setObjectName(QString::fromUtf8("alarma"));
        alarma->resize(400, 300);
        centralWidget = new QWidget(alarma);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        hores = new QLCDNumber(centralWidget);
        hores->setObjectName(QString::fromUtf8("hores"));

        gridLayout->addWidget(hores, 0, 0, 1, 1);

        minuts = new QLCDNumber(centralWidget);
        minuts->setObjectName(QString::fromUtf8("minuts"));

        gridLayout->addWidget(minuts, 0, 1, 1, 1);

        dialON = new QDial(centralWidget);
        dialON->setObjectName(QString::fromUtf8("dialON"));
        dialON->setMaximum(23);

        gridLayout->addWidget(dialON, 1, 0, 1, 1);

        dialOFF = new QDial(centralWidget);
        dialOFF->setObjectName(QString::fromUtf8("dialOFF"));
        dialOFF->setMaximum(59);
        dialOFF->setOrientation(Qt::Horizontal);
        dialOFF->setNotchTarget(3.7);

        gridLayout->addWidget(dialOFF, 1, 1, 1, 1);

        radioOn = new QRadioButton(centralWidget);
        radioOn->setObjectName(QString::fromUtf8("radioOn"));

        gridLayout->addWidget(radioOn, 2, 1, 1, 1);

        radioOff = new QRadioButton(centralWidget);
        radioOff->setObjectName(QString::fromUtf8("radioOff"));
        radioOff->setChecked(true);

        gridLayout->addWidget(radioOff, 3, 1, 1, 1);

        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        gridLayout->addWidget(resetButton, 4, 1, 1, 1);

        labelEstat = new MyQLabel(centralWidget);
        labelEstat->setObjectName(QString::fromUtf8("labelEstat"));
        labelEstat->setStyleSheet(QString::fromUtf8("background-color: red;\n"
"color: rgb(255, 255, 255);"));
        labelEstat->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelEstat, 3, 0, 2, 1);

        alarma->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(alarma);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        alarma->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(alarma);
        QObject::connect(dialON, SIGNAL(valueChanged(int)), hores, SLOT(display(int)));
        QObject::connect(dialOFF, SIGNAL(valueChanged(int)), minuts, SLOT(display(int)));
        QObject::connect(radioOn, SIGNAL(clicked()), labelEstat, SLOT(setOn()));
        QObject::connect(radioOff, SIGNAL(clicked()), labelEstat, SLOT(setOff()));
        QObject::connect(dialON, SIGNAL(valueChanged(int)), labelEstat, SLOT(setHour(int)));
        QObject::connect(dialOFF, SIGNAL(valueChanged(int)), labelEstat, SLOT(setMinute(int)));
        QObject::connect(resetButton, SIGNAL(clicked()), labelEstat, SLOT(reset()));
        QObject::connect(labelEstat, SIGNAL(enviaZero(int)), dialON, SLOT(setValue(int)));
        QObject::connect(labelEstat, SIGNAL(enviaZero(int)), dialOFF, SLOT(setValue(int)));
        QObject::connect(labelEstat, SIGNAL(radioOff2On(bool)), radioOff, SLOT(setChecked(bool)));

        QMetaObject::connectSlotsByName(alarma);
    } // setupUi

    void retranslateUi(QMainWindow *alarma)
    {
        alarma->setWindowTitle(QApplication::translate("alarma", "alarma", 0, QApplication::UnicodeUTF8));
        radioOn->setText(QApplication::translate("alarma", "ON", 0, QApplication::UnicodeUTF8));
        radioOff->setText(QApplication::translate("alarma", "OFF", 0, QApplication::UnicodeUTF8));
        resetButton->setText(QApplication::translate("alarma", "Reset", 0, QApplication::UnicodeUTF8));
        labelEstat->setText(QApplication::translate("alarma", "Alarma desactivada", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class alarma: public Ui_alarma {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALARMA_H
