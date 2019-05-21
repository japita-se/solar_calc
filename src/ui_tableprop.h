/********************************************************************************
** Form generated from reading UI file 'tableprop.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEPROP_H
#define UI_TABLEPROP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_tableprop
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinRow;
    QLabel *label_2;
    QSpinBox *spinCol;
    QDialogButtonBox *buttonBox;
    QLabel *label_3;
    QSpinBox *spinBorder;
    QComboBox *comboAlign;
    QLabel *label_4;
    QSpinBox *spinWidth;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QSpinBox *spinCellSpacing;
    QSpinBox *spinCellPadding;

    void setupUi(QDialog *tableprop)
    {
        if (tableprop->objectName().isEmpty())
            tableprop->setObjectName(QString::fromUtf8("tableprop"));
        tableprop->resize(324, 277);
        gridLayout = new QGridLayout(tableprop);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(tableprop);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinRow = new QSpinBox(tableprop);
        spinRow->setObjectName(QString::fromUtf8("spinRow"));
        spinRow->setValue(1);

        gridLayout->addWidget(spinRow, 0, 1, 1, 1);

        label_2 = new QLabel(tableprop);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spinCol = new QSpinBox(tableprop);
        spinCol->setObjectName(QString::fromUtf8("spinCol"));
        spinCol->setValue(1);

        gridLayout->addWidget(spinCol, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(tableprop);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 8, 0, 1, 2);

        label_3 = new QLabel(tableprop);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        spinBorder = new QSpinBox(tableprop);
        spinBorder->setObjectName(QString::fromUtf8("spinBorder"));
        spinBorder->setValue(1);

        gridLayout->addWidget(spinBorder, 2, 1, 1, 1);

        comboAlign = new QComboBox(tableprop);
        comboAlign->setObjectName(QString::fromUtf8("comboAlign"));

        gridLayout->addWidget(comboAlign, 3, 1, 1, 1);

        label_4 = new QLabel(tableprop);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        spinWidth = new QSpinBox(tableprop);
        spinWidth->setObjectName(QString::fromUtf8("spinWidth"));
        spinWidth->setMaximum(100);
        spinWidth->setValue(100);

        gridLayout->addWidget(spinWidth, 4, 1, 1, 1);

        label_5 = new QLabel(tableprop);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_6 = new QLabel(tableprop);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label_7 = new QLabel(tableprop);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        spinCellSpacing = new QSpinBox(tableprop);
        spinCellSpacing->setObjectName(QString::fromUtf8("spinCellSpacing"));

        gridLayout->addWidget(spinCellSpacing, 7, 1, 1, 1);

        spinCellPadding = new QSpinBox(tableprop);
        spinCellPadding->setObjectName(QString::fromUtf8("spinCellPadding"));

        gridLayout->addWidget(spinCellPadding, 5, 1, 1, 1);


        retranslateUi(tableprop);
        QObject::connect(buttonBox, SIGNAL(accepted()), tableprop, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), tableprop, SLOT(reject()));

        QMetaObject::connectSlotsByName(tableprop);
    } // setupUi

    void retranslateUi(QDialog *tableprop)
    {
        tableprop->setWindowTitle(QApplication::translate("tableprop", "Tabella", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("tableprop", "Righe", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("tableprop", "Colonne", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("tableprop", "Spessore", 0, QApplication::UnicodeUTF8));
        comboAlign->clear();
        comboAlign->insertItems(0, QStringList()
         << QApplication::translate("tableprop", "Sinistra", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("tableprop", "Centrato", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("tableprop", "Destra", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("tableprop", "Allineamento", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("tableprop", "Larghezza(%)", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("tableprop", "Spazio intercella", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("tableprop", "Spazio intracelle", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class tableprop: public Ui_tableprop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEPROP_H
