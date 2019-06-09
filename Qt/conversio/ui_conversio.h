/********************************************************************************
** Form generated from reading UI file 'conversio.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVERSIO_H
#define UI_CONVERSIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QDial *dial;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLCDNumber *lcdNumber_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLCDNumber *lcdNumber_3;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(455, 300);
        widget = new QWidget(Form);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 10, 394, 231));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        horizontalLayout->addWidget(spinBox);

        dial = new QDial(widget);
        dial->setObjectName(QStringLiteral("dial"));

        horizontalLayout->addWidget(dial);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("color: rgb(138, 226, 52);"));

        horizontalLayout_2->addWidget(label_2);

        lcdNumber = new QLCDNumber(widget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setStyleSheet(QStringLiteral("background-color: rgb(138, 226, 52);"));
        lcdNumber->setMode(QLCDNumber::Bin);

        horizontalLayout_2->addWidget(lcdNumber);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("color: rgb(114, 159, 207);"));

        horizontalLayout_3->addWidget(label_3);

        lcdNumber_2 = new QLCDNumber(widget);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setStyleSheet(QStringLiteral("background-color: rgb(114, 159, 207);"));
        lcdNumber_2->setMode(QLCDNumber::Oct);

        horizontalLayout_3->addWidget(lcdNumber_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QStringLiteral("color: rgb(239, 41, 41);"));

        horizontalLayout_4->addWidget(label_4);

        lcdNumber_3 = new QLCDNumber(widget);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));
        lcdNumber_3->setStyleSheet(QStringLiteral("background-color: rgb(239, 41, 41);"));
        lcdNumber_3->setMode(QLCDNumber::Hex);

        horizontalLayout_4->addWidget(lcdNumber_3);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout);

        widget1 = new QWidget(Form);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(60, 250, 341, 37));
        horizontalLayout_5 = new QHBoxLayout(widget1);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_5->addWidget(pushButton);


        retranslateUi(Form);
        QObject::connect(pushButton, SIGNAL(clicked()), Form, SLOT(close()));
        QObject::connect(dial, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), dial, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), lcdNumber_2, SLOT(display(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), lcdNumber_3, SLOT(display(int)));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        label->setText(QApplication::translate("Form", "Escriu un nombre natural:", nullptr));
        label_2->setText(QApplication::translate("Form", "Binari", nullptr));
        label_3->setText(QApplication::translate("Form", "Octal", nullptr));
        label_4->setText(QApplication::translate("Form", "Hexadecimal", nullptr));
        pushButton->setText(QApplication::translate("Form", "Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVERSIO_H
