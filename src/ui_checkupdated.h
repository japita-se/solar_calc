/********************************************************************************
** Form generated from reading UI file 'checkupdated.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKUPDATED_H
#define UI_CHECKUPDATED_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CheckUpdate
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *labelTop;
    QLabel *labelUpdate;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushOK;
    QCheckBox *checkStart;

    void setupUi(QDialog *CheckUpdate)
    {
        if (CheckUpdate->objectName().isEmpty())
            CheckUpdate->setObjectName(QString::fromUtf8("CheckUpdate"));
        CheckUpdate->resize(430, 272);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/logo3.png"), QSize(), QIcon::Normal, QIcon::Off);
        CheckUpdate->setWindowIcon(icon);
        CheckUpdate->setAutoFillBackground(false);
        CheckUpdate->setStyleSheet(QString::fromUtf8("border-color: white;\n"
"background-color: rgb(164, 189, 255);\n"
" background-clip: padding;"));
        gridLayout = new QGridLayout(CheckUpdate);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CheckUpdate);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(164, 189, 255)"));

        gridLayout->addWidget(label, 0, 0, 1, 3);

        labelTop = new QLabel(CheckUpdate);
        labelTop->setObjectName(QString::fromUtf8("labelTop"));
        labelTop->setStyleSheet(QString::fromUtf8("background-color: rgb(164, 189, 255)"));

        gridLayout->addWidget(labelTop, 1, 0, 1, 1);

        labelUpdate = new QLabel(CheckUpdate);
        labelUpdate->setObjectName(QString::fromUtf8("labelUpdate"));
        labelUpdate->setStyleSheet(QString::fromUtf8("background-color: rgb(164, 189, 255)"));
        labelUpdate->setWordWrap(true);

        gridLayout->addWidget(labelUpdate, 2, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(290, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 2);

        pushOK = new QPushButton(CheckUpdate);
        pushOK->setObjectName(QString::fromUtf8("pushOK"));

        gridLayout->addWidget(pushOK, 4, 2, 1, 1);

        checkStart = new QCheckBox(CheckUpdate);
        checkStart->setObjectName(QString::fromUtf8("checkStart"));

        gridLayout->addWidget(checkStart, 3, 1, 1, 2);


        retranslateUi(CheckUpdate);

        QMetaObject::connectSlotsByName(CheckUpdate);
    } // setupUi

    void retranslateUi(QDialog *CheckUpdate)
    {
        CheckUpdate->setWindowTitle(QApplication::translate("CheckUpdate", "Controllo aggiornamenti", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CheckUpdate", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img width=60 height=60 src=\":/images/logo3.png\" /></p>\n"
"<p style=\" margin-top:16px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:x-large; font-weight:600;\">SolarCalc 3, Controllo aggiornamenti</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        labelTop->setText(QApplication::translate("CheckUpdate", "Attendere.....", 0, QApplication::UnicodeUTF8));
        labelUpdate->setText(QString());
        pushOK->setText(QApplication::translate("CheckUpdate", "Ok", 0, QApplication::UnicodeUTF8));
        checkStart->setText(QApplication::translate("CheckUpdate", "Esegui sempre all'avvio", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CheckUpdate: public Ui_CheckUpdate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKUPDATED_H
