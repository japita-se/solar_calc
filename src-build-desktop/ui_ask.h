/********************************************************************************
** Form generated from reading UI file 'ask.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASK_H
#define UI_ASK_H

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

class Ui_Ask
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QCheckBox *checkNoMore;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushYes;
    QPushButton *pushNo;

    void setupUi(QDialog *Ask)
    {
        if (Ask->objectName().isEmpty())
            Ask->setObjectName(QString::fromUtf8("Ask"));
        Ask->resize(400, 200);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Ask->sizePolicy().hasHeightForWidth());
        Ask->setSizePolicy(sizePolicy);
        Ask->setMinimumSize(QSize(400, 200));
        Ask->setMaximumSize(QSize(400, 200));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        Ask->setWindowIcon(icon);
        gridLayout = new QGridLayout(Ask);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 0, 1, 1);

        label = new QLabel(Ask);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        gridLayout->addWidget(label, 1, 0, 1, 4);

        verticalSpacer = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        checkNoMore = new QCheckBox(Ask);
        checkNoMore->setObjectName(QString::fromUtf8("checkNoMore"));

        gridLayout->addWidget(checkNoMore, 3, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(263, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 1, 1, 1);

        pushYes = new QPushButton(Ask);
        pushYes->setObjectName(QString::fromUtf8("pushYes"));

        gridLayout->addWidget(pushYes, 4, 2, 1, 1);

        pushNo = new QPushButton(Ask);
        pushNo->setObjectName(QString::fromUtf8("pushNo"));

        gridLayout->addWidget(pushNo, 4, 3, 1, 1);


        retranslateUi(Ask);

        QMetaObject::connectSlotsByName(Ask);
    } // setupUi

    void retranslateUi(QDialog *Ask)
    {
        Ask->setWindowTitle(QApplication::translate("Ask", "Salvataggio carichi elettrici", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Ask", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Salvo i dati relativi al mese corrente? (se premi NO salvo i dati per tutti i mesi dell'anno)</p></body></html>", 0, QApplication::UnicodeUTF8));
        checkNoMore->setText(QApplication::translate("Ask", "Non chiedermelo ancora", 0, QApplication::UnicodeUTF8));
        pushYes->setText(QApplication::translate("Ask", "Si", 0, QApplication::UnicodeUTF8));
        pushNo->setText(QApplication::translate("Ask", "No", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Ask: public Ui_Ask {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASK_H
