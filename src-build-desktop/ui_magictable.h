/********************************************************************************
** Form generated from reading UI file 'magictable.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAGICTABLE_H
#define UI_MAGICTABLE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_MagicTable
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MagicTable)
    {
        if (MagicTable->objectName().isEmpty())
            MagicTable->setObjectName(QString::fromUtf8("MagicTable"));
        MagicTable->resize(664, 118);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/table.png"), QSize(), QIcon::Normal, QIcon::Off);
        MagicTable->setWindowIcon(icon);
        gridLayout = new QGridLayout(MagicTable);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tableWidget = new QTableWidget(MagicTable);
        if (tableWidget->columnCount() < 12)
            tableWidget->setColumnCount(12);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setRowCount(1);
        tableWidget->setColumnCount(12);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(50);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(40);
        tableWidget->verticalHeader()->setMinimumSectionSize(25);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(MagicTable);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(MagicTable);
        QObject::connect(buttonBox, SIGNAL(accepted()), MagicTable, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MagicTable, SLOT(reject()));

        QMetaObject::connectSlotsByName(MagicTable);
    } // setupUi

    void retranslateUi(QDialog *MagicTable)
    {
        MagicTable->setWindowTitle(QApplication::translate("MagicTable", "Perdite mensili", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MagicTable: public Ui_MagicTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAGICTABLE_H
