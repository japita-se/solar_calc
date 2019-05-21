/********************************************************************************
** Form generated from reading UI file 'albedo.ui'
**
** Created: Mon 25. Oct 20:49:53 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALBEDO_H
#define UI_ALBEDO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_Albedo
{
public:
    QGridLayout *gridLayout_2;
    QRadioButton *radioValori;
    QTableView *tableAlbedo;
    QRadioButton *radioMontagna;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioSnowHigh;
    QRadioButton *radioSnowLow;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Albedo)
    {
        if (Albedo->objectName().isEmpty())
            Albedo->setObjectName(QString::fromUtf8("Albedo"));
        Albedo->resize(491, 461);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/albedo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Albedo->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(Albedo);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioValori = new QRadioButton(Albedo);
        radioValori->setObjectName(QString::fromUtf8("radioValori"));
        radioValori->setChecked(true);

        gridLayout_2->addWidget(radioValori, 0, 0, 1, 1);

        tableAlbedo = new QTableView(Albedo);
        tableAlbedo->setObjectName(QString::fromUtf8("tableAlbedo"));
        tableAlbedo->setAlternatingRowColors(true);
        tableAlbedo->setSortingEnabled(true);

        gridLayout_2->addWidget(tableAlbedo, 1, 0, 1, 1);

        radioMontagna = new QRadioButton(Albedo);
        radioMontagna->setObjectName(QString::fromUtf8("radioMontagna"));

        gridLayout_2->addWidget(radioMontagna, 2, 0, 1, 1);

        groupBox = new QGroupBox(Albedo);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioSnowHigh = new QRadioButton(groupBox);
        radioSnowHigh->setObjectName(QString::fromUtf8("radioSnowHigh"));
        radioSnowHigh->setChecked(true);

        gridLayout->addWidget(radioSnowHigh, 0, 0, 1, 1);

        radioSnowLow = new QRadioButton(groupBox);
        radioSnowLow->setObjectName(QString::fromUtf8("radioSnowLow"));

        gridLayout->addWidget(radioSnowLow, 1, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Albedo);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 4, 0, 1, 1);


        retranslateUi(Albedo);
        QObject::connect(buttonBox, SIGNAL(accepted()), Albedo, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Albedo, SLOT(reject()));

        QMetaObject::connectSlotsByName(Albedo);
    } // setupUi

    void retranslateUi(QDialog *Albedo)
    {
        Albedo->setWindowTitle(QApplication::translate("Albedo", "Valori di albedo", 0, QApplication::UnicodeUTF8));
        radioValori->setText(QApplication::translate("Albedo", "Valori costanti", 0, QApplication::UnicodeUTF8));
        radioMontagna->setText(QApplication::translate("Albedo", "Zone di montagna", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox->setToolTip(QApplication::translate("Albedo", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Si considera \"Elevata precipitazione\" quando la somma della precipitazione per 3 mesi invernali &egrave; maggiore di 150mm.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("Albedo", "Caduta neve", 0, QApplication::UnicodeUTF8));
        radioSnowHigh->setText(QApplication::translate("Albedo", " Elevata precipitazione", 0, QApplication::UnicodeUTF8));
        radioSnowLow->setText(QApplication::translate("Albedo", "Moderata precipitazione", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Albedo: public Ui_Albedo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALBEDO_H
