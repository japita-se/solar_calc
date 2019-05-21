/********************************************************************************
** Form generated from reading UI file 'datipannello.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATIPANNELLO_H
#define UI_DATIPANNELLO_H

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
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DatiPannello
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineSearch;
    QComboBox *comboFilter;
    QLabel *label_3;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QTableView *tViewDatiPannello;
    QHBoxLayout *horizontalLayout_2;
    QDialogButtonBox *buttonBox;
    QPushButton *pushApplica;
    QPushButton *pushDelete;
    QListView *listMarca;

    void setupUi(QDialog *DatiPannello)
    {
        if (DatiPannello->objectName().isEmpty())
            DatiPannello->setObjectName(QString::fromUtf8("DatiPannello"));
        DatiPannello->resize(851, 304);
        gridLayout = new QGridLayout(DatiPannello);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DatiPannello);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineSearch = new QLineEdit(DatiPannello);
        lineSearch->setObjectName(QString::fromUtf8("lineSearch"));

        horizontalLayout->addWidget(lineSearch);

        comboFilter = new QComboBox(DatiPannello);
        comboFilter->setObjectName(QString::fromUtf8("comboFilter"));

        horizontalLayout->addWidget(comboFilter);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        label_3 = new QLabel(DatiPannello);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(DatiPannello);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tViewDatiPannello = new QTableView(DatiPannello);
        tViewDatiPannello->setObjectName(QString::fromUtf8("tViewDatiPannello"));
        tViewDatiPannello->setAlternatingRowColors(true);
        tViewDatiPannello->setSortingEnabled(true);
        tViewDatiPannello->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tViewDatiPannello->verticalHeader()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout->addWidget(tViewDatiPannello);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        buttonBox = new QDialogButtonBox(DatiPannello);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);

        pushApplica = new QPushButton(DatiPannello);
        pushApplica->setObjectName(QString::fromUtf8("pushApplica"));

        horizontalLayout_2->addWidget(pushApplica);

        pushDelete = new QPushButton(DatiPannello);
        pushDelete->setObjectName(QString::fromUtf8("pushDelete"));

        horizontalLayout_2->addWidget(pushDelete);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);

        listMarca = new QListView(DatiPannello);
        listMarca->setObjectName(QString::fromUtf8("listMarca"));
        listMarca->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(listMarca, 2, 0, 1, 1);


        retranslateUi(DatiPannello);
        QObject::connect(buttonBox, SIGNAL(accepted()), DatiPannello, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DatiPannello, SLOT(reject()));

        QMetaObject::connectSlotsByName(DatiPannello);
    } // setupUi

    void retranslateUi(QDialog *DatiPannello)
    {
        DatiPannello->setWindowTitle(QApplication::translate("DatiPannello", "Selezione pannello fv", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DatiPannello", "Cerca", 0, QApplication::UnicodeUTF8));
        comboFilter->clear();
        comboFilter->insertItems(0, QStringList()
         << QApplication::translate("DatiPannello", "Voc", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiPannello", "Efficienza", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiPannello", "Vmp", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiPannello", "Pnom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiPannello", "Costruttore", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiPannello", "Modello", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiPannello", "Dimensioni(mm)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DatiPannello", "Isc", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("DatiPannello", "Marca", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DatiPannello", "Dati", 0, QApplication::UnicodeUTF8));
        pushApplica->setText(QApplication::translate("DatiPannello", "Applica", 0, QApplication::UnicodeUTF8));
        pushDelete->setText(QApplication::translate("DatiPannello", "Elimina", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DatiPannello: public Ui_DatiPannello {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATIPANNELLO_H
