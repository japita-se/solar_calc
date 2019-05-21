/********************************************************************************
** Form generated from reading UI file 'chooselang.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSELANG_H
#define UI_CHOOSELANG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChooseLang
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboLang;
    QPushButton *okButton;
    QLabel *label_2;

    void setupUi(QDialog *ChooseLang)
    {
        if (ChooseLang->objectName().isEmpty())
            ChooseLang->setObjectName(QString::fromUtf8("ChooseLang"));
        ChooseLang->resize(320, 144);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChooseLang->sizePolicy().hasHeightForWidth());
        ChooseLang->setSizePolicy(sizePolicy);
        ChooseLang->setMaximumSize(QSize(320, 176));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/logo3.png"), QSize(), QIcon::Normal, QIcon::Off);
        ChooseLang->setWindowIcon(icon);
        gridLayout = new QGridLayout(ChooseLang);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(ChooseLang);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        comboLang = new QComboBox(ChooseLang);
        comboLang->setObjectName(QString::fromUtf8("comboLang"));

        gridLayout->addWidget(comboLang, 1, 1, 1, 2);

        okButton = new QPushButton(ChooseLang);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        gridLayout->addWidget(okButton, 2, 2, 1, 1);

        label_2 = new QLabel(ChooseLang);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(100, 100));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/logo3.png")));
        label_2->setScaledContents(true);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);


        retranslateUi(ChooseLang);

        QMetaObject::connectSlotsByName(ChooseLang);
    } // setupUi

    void retranslateUi(QDialog *ChooseLang)
    {
        ChooseLang->setWindowTitle(QApplication::translate("ChooseLang", "SolarCalc - startup", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ChooseLang", "Choose Language", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("ChooseLang", "Ok", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChooseLang: public Ui_ChooseLang {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSELANG_H
