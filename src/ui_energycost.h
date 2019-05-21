/********************************************************************************
** Form generated from reading UI file 'energycost.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENERGYCOST_H
#define UI_ENERGYCOST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgEnergyCost
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QComboBox *comboBox;
    QLabel *label;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBox_3;
    QLabel *label_4;
    QWidget *tab_2;

    void setupUi(QDialog *dlgEnergyCost)
    {
        if (dlgEnergyCost->objectName().isEmpty())
            dlgEnergyCost->setObjectName(QString::fromUtf8("dlgEnergyCost"));
        dlgEnergyCost->resize(560, 538);
        buttonBox = new QDialogButtonBox(dlgEnergyCost);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(170, 500, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(dlgEnergyCost);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 20, 521, 471));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(130, 60, 111, 25));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 101, 16));
        spinBox = new QSpinBox(tab);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(260, 60, 61, 26));
        spinBox_2 = new QSpinBox(tab);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(330, 60, 61, 26));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 40, 51, 16));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(330, 40, 101, 16));
        spinBox_3 = new QSpinBox(tab);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(400, 60, 91, 26));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(400, 40, 101, 16));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(dlgEnergyCost);
        QObject::connect(buttonBox, SIGNAL(accepted()), dlgEnergyCost, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dlgEnergyCost, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(dlgEnergyCost);
    } // setupUi

    void retranslateUi(QDialog *dlgEnergyCost)
    {
        dlgEnergyCost->setWindowTitle(QApplication::translate("dlgEnergyCost", "Dialog", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("dlgEnergyCost", "F1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgEnergyCost", "F2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgEnergyCost", "F3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgEnergyCost", "F4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgEnergyCost", "F5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgEnergyCost", "F6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgEnergyCost", "F (sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgEnergyCost", "F (domenica)", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("dlgEnergyCost", "Denominazione", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("dlgEnergyCost", "Da", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("dlgEnergyCost", "A", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("dlgEnergyCost", "Valore/kWh", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("dlgEnergyCost", "Fasce orarie di costo", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("dlgEnergyCost", "Prezzi energia", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgEnergyCost: public Ui_dlgEnergyCost {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENERGYCOST_H
