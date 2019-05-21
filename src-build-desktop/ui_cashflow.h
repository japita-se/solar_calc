/********************************************************************************
** Form generated from reading UI file 'cashflow.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CASHFLOW_H
#define UI_CASHFLOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_widgetCashFlow
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QwtPlot *qwtPlot;
    QwtPlot *qwtVan;
    QCheckBox *checkCumulative;
    QCheckBox *checkRata;
    QWidget *tabTabella;
    QGridLayout *gridLayout_3;
    QTextEdit *textEdit;
    QWidget *tabSSPDetails;
    QGridLayout *gridLayout_4;
    QTextEdit *textEditCS;

    void setupUi(QWidget *widgetCashFlow)
    {
        if (widgetCashFlow->objectName().isEmpty())
            widgetCashFlow->setObjectName(QString::fromUtf8("widgetCashFlow"));
        widgetCashFlow->resize(992, 821);
        gridLayout = new QGridLayout(widgetCashFlow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(widgetCashFlow);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        qwtPlot = new QwtPlot(tab);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));

        gridLayout_2->addWidget(qwtPlot, 0, 0, 1, 2);

        qwtVan = new QwtPlot(tab);
        qwtVan->setObjectName(QString::fromUtf8("qwtVan"));

        gridLayout_2->addWidget(qwtVan, 1, 0, 1, 2);

        checkCumulative = new QCheckBox(tab);
        checkCumulative->setObjectName(QString::fromUtf8("checkCumulative"));

        gridLayout_2->addWidget(checkCumulative, 2, 0, 1, 1);

        checkRata = new QCheckBox(tab);
        checkRata->setObjectName(QString::fromUtf8("checkRata"));

        gridLayout_2->addWidget(checkRata, 2, 1, 1, 1);

        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/plot.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon, QString());
        tabTabella = new QWidget();
        tabTabella->setObjectName(QString::fromUtf8("tabTabella"));
        gridLayout_3 = new QGridLayout(tabTabella);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        textEdit = new QTextEdit(tabTabella);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_3->addWidget(textEdit, 0, 0, 1, 1);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/table.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tabTabella, icon1, QString());
        tabSSPDetails = new QWidget();
        tabSSPDetails->setObjectName(QString::fromUtf8("tabSSPDetails"));
        gridLayout_4 = new QGridLayout(tabSSPDetails);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        textEditCS = new QTextEdit(tabSSPDetails);
        textEditCS->setObjectName(QString::fromUtf8("textEditCS"));

        gridLayout_4->addWidget(textEditCS, 0, 0, 1, 1);

        tabWidget->addTab(tabSSPDetails, icon1, QString());

        gridLayout->addWidget(tabWidget, 1, 0, 1, 1);


        retranslateUi(widgetCashFlow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(widgetCashFlow);
    } // setupUi

    void retranslateUi(QWidget *widgetCashFlow)
    {
        widgetCashFlow->setWindowTitle(QApplication::translate("widgetCashFlow", "Form", 0, QApplication::UnicodeUTF8));
        checkCumulative->setText(QApplication::translate("widgetCashFlow", "Visualizza valori cumulativi", 0, QApplication::UnicodeUTF8));
        checkRata->setText(QApplication::translate("widgetCashFlow", "Visualizza rata mutuo", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("widgetCashFlow", "Grafici", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabTabella), QApplication::translate("widgetCashFlow", "Risultati Sim.", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabSSPDetails), QApplication::translate("widgetCashFlow", "Dettagli CS", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class widgetCashFlow: public Ui_widgetCashFlow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASHFLOW_H
