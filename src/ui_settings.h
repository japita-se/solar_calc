/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineAsseY;
    QLabel *label_4;
    QLineEdit *lineAsseYRight;
    QRadioButton *radioMJ;
    QRadioButton *radiokWh;
    QLabel *label_2;
    QLineEdit *lineAsseX;
    QLabel *label_3;
    QLineEdit *lineTitolo;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QString::fromUtf8("Settings"));
        Settings->resize(489, 292);
        verticalLayout = new QVBoxLayout(Settings);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(Settings);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineAsseY = new QLineEdit(Settings);
        lineAsseY->setObjectName(QString::fromUtf8("lineAsseY"));

        gridLayout->addWidget(lineAsseY, 0, 1, 1, 2);

        label_4 = new QLabel(Settings);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        lineAsseYRight = new QLineEdit(Settings);
        lineAsseYRight->setObjectName(QString::fromUtf8("lineAsseYRight"));

        gridLayout->addWidget(lineAsseYRight, 1, 1, 1, 2);

        radioMJ = new QRadioButton(Settings);
        radioMJ->setObjectName(QString::fromUtf8("radioMJ"));

        gridLayout->addWidget(radioMJ, 2, 0, 1, 2);

        radiokWh = new QRadioButton(Settings);
        radiokWh->setObjectName(QString::fromUtf8("radiokWh"));

        gridLayout->addWidget(radiokWh, 3, 0, 1, 3);

        label_2 = new QLabel(Settings);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        lineAsseX = new QLineEdit(Settings);
        lineAsseX->setObjectName(QString::fromUtf8("lineAsseX"));

        gridLayout->addWidget(lineAsseX, 4, 2, 1, 1);

        label_3 = new QLabel(Settings);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 5, 0, 1, 1);

        lineTitolo = new QLineEdit(Settings);
        lineTitolo->setObjectName(QString::fromUtf8("lineTitolo"));

        gridLayout->addWidget(lineTitolo, 5, 2, 1, 1);

        buttonBox = new QDialogButtonBox(Settings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 0, 1, 3);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(Settings);
        QObject::connect(buttonBox, SIGNAL(accepted()), Settings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Impostazioni grafico", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Settings", "Titolo sinistro", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Settings", "Titolo destro", 0, QApplication::UnicodeUTF8));
        radioMJ->setText(QApplication::translate("Settings", "MJ/m2 giorno", 0, QApplication::UnicodeUTF8));
        radiokWh->setText(QApplication::translate("Settings", "kWh/m2 giorno", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Settings", "Asse X", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Settings", "Titolo grafico", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
