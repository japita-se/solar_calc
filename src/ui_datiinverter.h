/********************************************************************************
** Form generated from reading UI file 'datiinverter.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATIINVERTER_H
#define UI_DATIINVERTER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_DatiInverter
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineSearch;
    QComboBox *comboFilter;
    QLabel *label_3;
    QLabel *label_2;
    QListView *listMarca;
    QTableView *tViewDatiInverter;
    QHBoxLayout *horizontalLayout_2;
    QDialogButtonBox *buttonBox;
    QPushButton *pushApplica;
    QPushButton *pushElimina;

    void setupUi(QDialog *DatiInverter)
    {
        if (DatiInverter->objectName().isEmpty())
            DatiInverter->setObjectName(QString::fromUtf8("DatiInverter"));
        DatiInverter->resize(851, 304);
        gridLayout = new QGridLayout(DatiInverter);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DatiInverter);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineSearch = new QLineEdit(DatiInverter);
        lineSearch->setObjectName(QString::fromUtf8("lineSearch"));

        horizontalLayout->addWidget(lineSearch);

        comboFilter = new QComboBox(DatiInverter);
        comboFilter->setObjectName(QString::fromUtf8("comboFilter"));

        horizontalLayout->addWidget(comboFilter);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        label_3 = new QLabel(DatiInverter);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(DatiInverter);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        listMarca = new QListView(DatiInverter);
        listMarca->setObjectName(QString::fromUtf8("listMarca"));
        listMarca->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(listMarca, 2, 0, 1, 1);

        tViewDatiInverter = new QTableView(DatiInverter);
        tViewDatiInverter->setObjectName(QString::fromUtf8("tViewDatiInverter"));
        tViewDatiInverter->setAlternatingRowColors(true);
        tViewDatiInverter->setSortingEnabled(true);

        gridLayout->addWidget(tViewDatiInverter, 2, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        buttonBox = new QDialogButtonBox(DatiInverter);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);

        pushApplica = new QPushButton(DatiInverter);
        pushApplica->setObjectName(QString::fromUtf8("pushApplica"));

        horizontalLayout_2->addWidget(pushApplica);

        pushElimina = new QPushButton(DatiInverter);
        pushElimina->setObjectName(QString::fromUtf8("pushElimina"));

        horizontalLayout_2->addWidget(pushElimina);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 1, 1);


        retranslateUi(DatiInverter);
        QObject::connect(buttonBox, SIGNAL(rejected()), DatiInverter, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), DatiInverter, SLOT(accept()));

        QMetaObject::connectSlotsByName(DatiInverter);
    } // setupUi

    void retranslateUi(QDialog *DatiInverter)
    {
        DatiInverter->setWindowTitle(QApplication::translate("DatiInverter", "Selezione inverter", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DatiInverter", "Cerca", 0, QApplication::UnicodeUTF8));
        comboFilter->clear();
        comboFilter->insertItems(0, QStringList()
         << QApplication::translate("DatiInverter", "Efficienza", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "Vmp", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "Pnom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "Costruttore", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "Modello", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "Vmin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "Vmax", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "Vmpmin", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "Vmpmax", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiInverter", "tipo", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("DatiInverter", "Marca", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DatiInverter", "Dati", 0, QApplication::UnicodeUTF8));
        pushApplica->setText(QApplication::translate("DatiInverter", "Applica", 0, QApplication::UnicodeUTF8));
        pushElimina->setText(QApplication::translate("DatiInverter", "Elimina", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DatiInverter: public Ui_DatiInverter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATIINVERTER_H
