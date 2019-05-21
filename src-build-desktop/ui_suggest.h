/********************************************************************************
** Form generated from reading UI file 'suggest.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUGGEST_H
#define UI_SUGGEST_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Suggest
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QRadioButton *radiokWh;
    QDoubleSpinBox *dSpinBoxConsumi;
    QRadioButton *radiokW;
    QDoubleSpinBox *dSpinBoxPotenza;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *labelArea;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLabel *labelNum;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushOK;
    QPushButton *pushCancel;

    void setupUi(QDialog *Suggest)
    {
        if (Suggest->objectName().isEmpty())
            Suggest->setObjectName(QString::fromUtf8("Suggest"));
        Suggest->resize(348, 364);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/wizard.png"), QSize(), QIcon::Normal, QIcon::Off);
        Suggest->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(Suggest);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_2 = new QGroupBox(Suggest);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radiokWh = new QRadioButton(groupBox_2);
        radiokWh->setObjectName(QString::fromUtf8("radiokWh"));
        radiokWh->setChecked(true);

        gridLayout->addWidget(radiokWh, 0, 0, 1, 1);

        dSpinBoxConsumi = new QDoubleSpinBox(groupBox_2);
        dSpinBoxConsumi->setObjectName(QString::fromUtf8("dSpinBoxConsumi"));
        dSpinBoxConsumi->setMaximum(1e+07);
        dSpinBoxConsumi->setValue(0);

        gridLayout->addWidget(dSpinBoxConsumi, 0, 1, 1, 1);

        radiokW = new QRadioButton(groupBox_2);
        radiokW->setObjectName(QString::fromUtf8("radiokW"));

        gridLayout->addWidget(radiokW, 1, 0, 1, 1);

        dSpinBoxPotenza = new QDoubleSpinBox(groupBox_2);
        dSpinBoxPotenza->setObjectName(QString::fromUtf8("dSpinBoxPotenza"));
        dSpinBoxPotenza->setMaximum(1e+09);

        gridLayout->addWidget(dSpinBoxPotenza, 1, 1, 1, 1);


        gridLayout_2->addWidget(groupBox_2, 0, 0, 1, 3);

        groupBox = new QGroupBox(Suggest);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setAutoFillBackground(false);
        groupBox->setLocale(QLocale(QLocale::Italian, QLocale::Italy));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        labelArea = new QLabel(groupBox);
        labelArea->setObjectName(QString::fromUtf8("labelArea"));

        horizontalLayout_3->addWidget(labelArea);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        labelNum = new QLabel(groupBox);
        labelNum->setObjectName(QString::fromUtf8("labelNum"));

        horizontalLayout_4->addWidget(labelNum);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(165, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        pushOK = new QPushButton(Suggest);
        pushOK->setObjectName(QString::fromUtf8("pushOK"));

        gridLayout_2->addWidget(pushOK, 2, 1, 1, 1);

        pushCancel = new QPushButton(Suggest);
        pushCancel->setObjectName(QString::fromUtf8("pushCancel"));

        gridLayout_2->addWidget(pushCancel, 2, 2, 1, 1);


        retranslateUi(Suggest);

        QMetaObject::connectSlotsByName(Suggest);
    } // setupUi

    void retranslateUi(QDialog *Suggest)
    {
        Suggest->setWindowTitle(QApplication::translate("Suggest", "SolarCalc", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Suggest", "Criterio di progetto", 0, QApplication::UnicodeUTF8));
        radiokWh->setText(QApplication::translate("Suggest", "Consumi annuali (kWh)", 0, QApplication::UnicodeUTF8));
        radiokW->setText(QApplication::translate("Suggest", "Potenza installata (Wp)", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Suggest", "Risultati - senza perdite", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Suggest", "Area (mq)", 0, QApplication::UnicodeUTF8));
        labelArea->setText(QApplication::translate("Suggest", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Suggest", "N. pannelli", 0, QApplication::UnicodeUTF8));
        labelNum->setText(QApplication::translate("Suggest", "0", 0, QApplication::UnicodeUTF8));
        pushOK->setText(QApplication::translate("Suggest", "OK", 0, QApplication::UnicodeUTF8));
        pushCancel->setText(QApplication::translate("Suggest", "Annulla", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Suggest: public Ui_Suggest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUGGEST_H
