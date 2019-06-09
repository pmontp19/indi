/********************************************************************************
** Form generated from reading UI file 'rellotge.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RELLOTGE_H
#define UI_RELLOTGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rellotge
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *labelhours;
    QLCDNumber *lcdhours;
    QDial *dialhours;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelminutes;
    QLCDNumber *lcdminutes;
    QDial *dialminutes;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *exitbutton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *rellotge)
    {
        if (rellotge->objectName().isEmpty())
            rellotge->setObjectName(QStringLiteral("rellotge"));
        rellotge->resize(400, 347);
        centralWidget = new QWidget(rellotge);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelhours = new QLabel(centralWidget);
        labelhours->setObjectName(QStringLiteral("labelhours"));

        verticalLayout->addWidget(labelhours);

        lcdhours = new QLCDNumber(centralWidget);
        lcdhours->setObjectName(QStringLiteral("lcdhours"));
        lcdhours->setMinimumSize(QSize(0, 60));
        lcdhours->setLineWidth(1);

        verticalLayout->addWidget(lcdhours);

        dialhours = new QDial(centralWidget);
        dialhours->setObjectName(QStringLiteral("dialhours"));
        dialhours->setMaximum(23);

        verticalLayout->addWidget(dialhours);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelminutes = new QLabel(centralWidget);
        labelminutes->setObjectName(QStringLiteral("labelminutes"));

        verticalLayout_2->addWidget(labelminutes);

        lcdminutes = new QLCDNumber(centralWidget);
        lcdminutes->setObjectName(QStringLiteral("lcdminutes"));
        lcdminutes->setMinimumSize(QSize(0, 60));

        verticalLayout_2->addWidget(lcdminutes);

        dialminutes = new QDial(centralWidget);
        dialminutes->setObjectName(QStringLiteral("dialminutes"));
        dialminutes->setMaximum(59);

        verticalLayout_2->addWidget(dialminutes);


        horizontalLayout_2->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        exitbutton = new QPushButton(centralWidget);
        exitbutton->setObjectName(QStringLiteral("exitbutton"));

        horizontalLayout->addWidget(exitbutton);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        rellotge->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(rellotge);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        rellotge->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(rellotge);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        rellotge->setStatusBar(statusBar);

        retranslateUi(rellotge);
        QObject::connect(dialhours, SIGNAL(valueChanged(int)), lcdhours, SLOT(display(int)));
        QObject::connect(dialminutes, SIGNAL(valueChanged(int)), lcdminutes, SLOT(display(int)));
        QObject::connect(exitbutton, SIGNAL(clicked()), rellotge, SLOT(close()));

        QMetaObject::connectSlotsByName(rellotge);
    } // setupUi

    void retranslateUi(QMainWindow *rellotge)
    {
        rellotge->setWindowTitle(QApplication::translate("rellotge", "rellotge", nullptr));
        labelhours->setText(QApplication::translate("rellotge", "Hores", nullptr));
        labelminutes->setText(QApplication::translate("rellotge", "Minuts", nullptr));
        exitbutton->setText(QApplication::translate("rellotge", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class rellotge: public Ui_rellotge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RELLOTGE_H
