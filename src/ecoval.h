/********************************************************************************
** Form generated from reading ui file 'ecoval.ui'
**
** Created: Tue Jul 21 09:29:35 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef ECOVAL_H
#define ECOVAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_widgetEcoVal
{
public:
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_16;
    QGroupBox *groupBands;
    QGridLayout *gridLayout_13;
    QListView *listBands;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_5;
    QComboBox *comboBands;
    QSpinBox *spinDa;
    QSpinBox *spinA;
    QDoubleSpinBox *dValue;
    QLabel *label_4;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushSaveBandsAs;
    QPushButton *pushSaveBands;
    QPushButton *pushLoadBands;
    QWidget *tabPrezzi;
    QGridLayout *gridLayout_17;
    QGridLayout *gridLayout_15;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_5;
    QLabel *label_23;
    QDoubleSpinBox *dTrasmissione;
    QLabel *label_22;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QLabel *label_21;
    QDoubleSpinBox *dDistribuzioneWh;
    QLabel *label_25;
    QDoubleSpinBox *dDistribuzioneW;
    QLabel *label_26;
    QDoubleSpinBox *dDistribuzioneAnno;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_8;
    QLabel *label_31;
    QDoubleSpinBox *dPerditaTrasmissione;
    QLabel *label_33;
    QDoubleSpinBox *dPerditaDistribuzione;
    QLabel *label_34;
    QDoubleSpinBox *dCTRkWh;
    QLabel *label_36;
    QDoubleSpinBox *dAltriCostickWh;
    QLabel *label_35;
    QDoubleSpinBox *dAltriCostiMensili;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_6;
    QDoubleSpinBox *dMisurakWh;
    QLabel *label_32;
    QDoubleSpinBox *dMisuraAnno;
    QLabel *label_30;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_11;
    QDoubleSpinBox *dAUC;
    QLabel *label_9;
    QGridLayout *gridLayout_7;
    QComboBox *comboRecent;
    QPushButton *pushSavePrezzi;
    QPushButton *pushSavePrezziAs;
    QPushButton *pushLoadPrezzi;
    QGroupBox *groupPrezzi;
    QGridLayout *gridLayout_14;
    QTableWidget *tablePrezziEnergia;
    QGridLayout *gridLayout_9;
    QPushButton *pushSavePrezziEnergia;
    QPushButton *pushSavePrezziEnergiaAs;
    QPushButton *pushLoadPrezziEnergia;
    QListView *listEnergyPrices;
    QwtPlot *qwtPrezzi;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QDoubleSpinBox *dAREnergyRate;
    QWidget *tabEconomici;
    QGridLayout *gridLayout_19;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_18;
    QComboBox *comboRegime;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QDoubleSpinBox *dARCH;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_24;
    QDoubleSpinBox *dMinEnergyPrice;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_14;
    QDoubleSpinBox *dIncentivi;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_20;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_11;
    QDoubleSpinBox *dManutenzioneAnno;
    QLabel *label_12;
    QDoubleSpinBox *dTasse;
    QLabel *label_13;
    QDoubleSpinBox *dAffitti;
    QLabel *label_17;
    QDoubleSpinBox *dAltro;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_10;
    QLabel *label_27;
    QDoubleSpinBox *dCostoIniziale;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_28;
    QDoubleSpinBox *dFinanziamento;
    QDoubleSpinBox *dFinAnni;
    QLabel *label_29;
    QGridLayout *gridLayout_3;
    QLabel *label_15;
    QDoubleSpinBox *dTassoInflazione;
    QLabel *label_19;
    QDoubleSpinBox *dEnergyInflationRate;
    QLabel *label_16;
    QDoubleSpinBox *dLoanInterestRate;
    QLabel *label_2;
    QDoubleSpinBox *dDisscountRate;
    QLabel *label_18;
    QDoubleSpinBox *dPeriodo;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushSave_3;
    QPushButton *pushLoad_3;
    QWidget *tab_2;
    QGridLayout *gridLayout_12;
    QwtPlot *qwtVan;
    QwtPlot *qwtPlot;
    QWidget *page_3;
    QWidget *page_2;

    void setupUi(QWidget *widgetEcoVal)
    {
        if (widgetEcoVal->objectName().isEmpty())
            widgetEcoVal->setObjectName(QString::fromUtf8("widgetEcoVal"));
        widgetEcoVal->resize(992, 821);
        verticalLayout_2 = new QVBoxLayout(widgetEcoVal);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        stackedWidget = new QStackedWidget(widgetEcoVal);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayout_3 = new QHBoxLayout(page);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tabWidget = new QTabWidget(page);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_16 = new QGridLayout(tab);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        groupBands = new QGroupBox(tab);
        groupBands->setObjectName(QString::fromUtf8("groupBands"));
        groupBands->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_13 = new QGridLayout(groupBands);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        listBands = new QListView(groupBands);
        listBands->setObjectName(QString::fromUtf8("listBands"));
        listBands->setMinimumSize(QSize(144, 53));

        gridLayout_13->addWidget(listBands, 0, 0, 4, 1);

        horizontalSpacer_4 = new QSpacerItem(242, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_4, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_7 = new QLabel(groupBands);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 2, 1, 1);

        label_6 = new QLabel(groupBands);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 3, 1, 1);

        label_8 = new QLabel(groupBands);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 4, 1, 1);

        label_5 = new QLabel(groupBands);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        comboBands = new QComboBox(groupBands);
        comboBands->setObjectName(QString::fromUtf8("comboBands"));

        gridLayout->addWidget(comboBands, 1, 1, 1, 1);

        spinDa = new QSpinBox(groupBands);
        spinDa->setObjectName(QString::fromUtf8("spinDa"));
        spinDa->setMaximum(23);

        gridLayout->addWidget(spinDa, 1, 2, 1, 1);

        spinA = new QSpinBox(groupBands);
        spinA->setObjectName(QString::fromUtf8("spinA"));
        spinA->setMaximum(23);

        gridLayout->addWidget(spinA, 1, 3, 1, 1);

        dValue = new QDoubleSpinBox(groupBands);
        dValue->setObjectName(QString::fromUtf8("dValue"));
        dValue->setMaximum(10000);

        gridLayout->addWidget(dValue, 1, 4, 1, 1);


        gridLayout_13->addLayout(gridLayout, 0, 2, 1, 1);

        label_4 = new QLabel(groupBands);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(90, 18));

        gridLayout_13->addWidget(label_4, 1, 1, 1, 1);

        label_3 = new QLabel(groupBands);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(90, 18));

        gridLayout_13->addWidget(label_3, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 213, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_13->addItem(verticalSpacer, 3, 2, 1, 1);


        gridLayout_16->addWidget(groupBands, 0, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 346, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_16->addItem(verticalSpacer_4, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushSaveBandsAs = new QPushButton(tab);
        pushSaveBandsAs->setObjectName(QString::fromUtf8("pushSaveBandsAs"));

        horizontalLayout->addWidget(pushSaveBandsAs);

        pushSaveBands = new QPushButton(tab);
        pushSaveBands->setObjectName(QString::fromUtf8("pushSaveBands"));

        horizontalLayout->addWidget(pushSaveBands);

        pushLoadBands = new QPushButton(tab);
        pushLoadBands->setObjectName(QString::fromUtf8("pushLoadBands"));

        horizontalLayout->addWidget(pushLoadBands);


        gridLayout_16->addLayout(horizontalLayout, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tabPrezzi = new QWidget();
        tabPrezzi->setObjectName(QString::fromUtf8("tabPrezzi"));
        gridLayout_17 = new QGridLayout(tabPrezzi);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        groupBox_4 = new QGroupBox(tabPrezzi);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_5 = new QGridLayout(groupBox_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_23 = new QLabel(groupBox_4);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_5->addWidget(label_23, 0, 0, 1, 1);

        dTrasmissione = new QDoubleSpinBox(groupBox_4);
        dTrasmissione->setObjectName(QString::fromUtf8("dTrasmissione"));
        dTrasmissione->setDecimals(3);
        dTrasmissione->setMaximum(20000);
        dTrasmissione->setSingleStep(1);

        gridLayout_5->addWidget(dTrasmissione, 0, 1, 1, 1);


        gridLayout_15->addWidget(groupBox_4, 0, 0, 1, 1);

        label_22 = new QLabel(tabPrezzi);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setWordWrap(true);

        gridLayout_15->addWidget(label_22, 0, 1, 2, 1);

        groupBox_6 = new QGroupBox(tabPrezzi);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_21 = new QLabel(groupBox_6);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_4->addWidget(label_21, 0, 0, 1, 1);

        dDistribuzioneWh = new QDoubleSpinBox(groupBox_6);
        dDistribuzioneWh->setObjectName(QString::fromUtf8("dDistribuzioneWh"));
        dDistribuzioneWh->setDecimals(3);
        dDistribuzioneWh->setMaximum(20000);
        dDistribuzioneWh->setSingleStep(1);

        gridLayout_4->addWidget(dDistribuzioneWh, 0, 1, 1, 1);

        label_25 = new QLabel(groupBox_6);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_4->addWidget(label_25, 1, 0, 1, 1);

        dDistribuzioneW = new QDoubleSpinBox(groupBox_6);
        dDistribuzioneW->setObjectName(QString::fromUtf8("dDistribuzioneW"));
        dDistribuzioneW->setDecimals(3);
        dDistribuzioneW->setMaximum(20000);

        gridLayout_4->addWidget(dDistribuzioneW, 1, 1, 1, 1);

        label_26 = new QLabel(groupBox_6);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_4->addWidget(label_26, 2, 0, 1, 1);

        dDistribuzioneAnno = new QDoubleSpinBox(groupBox_6);
        dDistribuzioneAnno->setObjectName(QString::fromUtf8("dDistribuzioneAnno"));
        dDistribuzioneAnno->setDecimals(3);
        dDistribuzioneAnno->setMaximum(20000);

        gridLayout_4->addWidget(dDistribuzioneAnno, 2, 1, 1, 1);


        gridLayout_15->addWidget(groupBox_6, 1, 0, 2, 1);

        groupBox_8 = new QGroupBox(tabPrezzi);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_8 = new QGridLayout(groupBox_8);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_31 = new QLabel(groupBox_8);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_8->addWidget(label_31, 0, 0, 1, 1);

        dPerditaTrasmissione = new QDoubleSpinBox(groupBox_8);
        dPerditaTrasmissione->setObjectName(QString::fromUtf8("dPerditaTrasmissione"));
        dPerditaTrasmissione->setMaximum(100);

        gridLayout_8->addWidget(dPerditaTrasmissione, 0, 1, 1, 1);

        label_33 = new QLabel(groupBox_8);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_8->addWidget(label_33, 1, 0, 1, 1);

        dPerditaDistribuzione = new QDoubleSpinBox(groupBox_8);
        dPerditaDistribuzione->setObjectName(QString::fromUtf8("dPerditaDistribuzione"));
        dPerditaDistribuzione->setMaximum(100);

        gridLayout_8->addWidget(dPerditaDistribuzione, 1, 1, 1, 1);

        label_34 = new QLabel(groupBox_8);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_8->addWidget(label_34, 2, 0, 1, 1);

        dCTRkWh = new QDoubleSpinBox(groupBox_8);
        dCTRkWh->setObjectName(QString::fromUtf8("dCTRkWh"));
        dCTRkWh->setMaximum(1e+09);

        gridLayout_8->addWidget(dCTRkWh, 2, 1, 1, 1);

        label_36 = new QLabel(groupBox_8);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_8->addWidget(label_36, 3, 0, 1, 1);

        dAltriCostickWh = new QDoubleSpinBox(groupBox_8);
        dAltriCostickWh->setObjectName(QString::fromUtf8("dAltriCostickWh"));

        gridLayout_8->addWidget(dAltriCostickWh, 3, 1, 1, 1);

        label_35 = new QLabel(groupBox_8);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_8->addWidget(label_35, 4, 0, 1, 1);

        dAltriCostiMensili = new QDoubleSpinBox(groupBox_8);
        dAltriCostiMensili->setObjectName(QString::fromUtf8("dAltriCostiMensili"));

        gridLayout_8->addWidget(dAltriCostiMensili, 4, 1, 1, 1);


        gridLayout_15->addWidget(groupBox_8, 2, 1, 3, 1);

        groupBox_5 = new QGroupBox(tabPrezzi);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_6 = new QGridLayout(groupBox_5);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        dMisurakWh = new QDoubleSpinBox(groupBox_5);
        dMisurakWh->setObjectName(QString::fromUtf8("dMisurakWh"));
        dMisurakWh->setDecimals(3);
        dMisurakWh->setMaximum(20000);
        dMisurakWh->setSingleStep(1);

        gridLayout_6->addWidget(dMisurakWh, 0, 1, 1, 1);

        label_32 = new QLabel(groupBox_5);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_6->addWidget(label_32, 1, 0, 1, 1);

        dMisuraAnno = new QDoubleSpinBox(groupBox_5);
        dMisuraAnno->setObjectName(QString::fromUtf8("dMisuraAnno"));
        dMisuraAnno->setDecimals(3);
        dMisuraAnno->setMaximum(20000);

        gridLayout_6->addWidget(dMisuraAnno, 1, 1, 1, 1);

        label_30 = new QLabel(groupBox_5);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_6->addWidget(label_30, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_5, 3, 0, 1, 1);

        groupBox_7 = new QGroupBox(tabPrezzi);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_11 = new QGridLayout(groupBox_7);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        dAUC = new QDoubleSpinBox(groupBox_7);
        dAUC->setObjectName(QString::fromUtf8("dAUC"));
        dAUC->setDecimals(3);
        dAUC->setMaximum(2e+06);

        gridLayout_11->addWidget(dAUC, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_7);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_11->addWidget(label_9, 0, 0, 1, 1);


        gridLayout_15->addWidget(groupBox_7, 4, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        comboRecent = new QComboBox(tabPrezzi);
        comboRecent->setObjectName(QString::fromUtf8("comboRecent"));
        comboRecent->setMinimumSize(QSize(200, 0));

        gridLayout_7->addWidget(comboRecent, 0, 0, 1, 1);

        pushSavePrezzi = new QPushButton(tabPrezzi);
        pushSavePrezzi->setObjectName(QString::fromUtf8("pushSavePrezzi"));

        gridLayout_7->addWidget(pushSavePrezzi, 0, 1, 1, 1);

        pushSavePrezziAs = new QPushButton(tabPrezzi);
        pushSavePrezziAs->setObjectName(QString::fromUtf8("pushSavePrezziAs"));

        gridLayout_7->addWidget(pushSavePrezziAs, 0, 2, 1, 1);

        pushLoadPrezzi = new QPushButton(tabPrezzi);
        pushLoadPrezzi->setObjectName(QString::fromUtf8("pushLoadPrezzi"));

        gridLayout_7->addWidget(pushLoadPrezzi, 0, 3, 1, 1);


        gridLayout_15->addLayout(gridLayout_7, 5, 1, 1, 1);


        gridLayout_17->addLayout(gridLayout_15, 0, 0, 1, 1);

        groupPrezzi = new QGroupBox(tabPrezzi);
        groupPrezzi->setObjectName(QString::fromUtf8("groupPrezzi"));
        groupPrezzi->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_14 = new QGridLayout(groupPrezzi);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        tablePrezziEnergia = new QTableWidget(groupPrezzi);
        if (tablePrezziEnergia->columnCount() < 1)
            tablePrezziEnergia->setColumnCount(1);
        if (tablePrezziEnergia->rowCount() < 12)
            tablePrezziEnergia->setRowCount(12);
        tablePrezziEnergia->setObjectName(QString::fromUtf8("tablePrezziEnergia"));
        tablePrezziEnergia->setRowCount(12);
        tablePrezziEnergia->setColumnCount(1);

        gridLayout_14->addWidget(tablePrezziEnergia, 0, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        pushSavePrezziEnergia = new QPushButton(groupPrezzi);
        pushSavePrezziEnergia->setObjectName(QString::fromUtf8("pushSavePrezziEnergia"));

        gridLayout_9->addWidget(pushSavePrezziEnergia, 0, 0, 1, 1);

        pushSavePrezziEnergiaAs = new QPushButton(groupPrezzi);
        pushSavePrezziEnergiaAs->setObjectName(QString::fromUtf8("pushSavePrezziEnergiaAs"));

        gridLayout_9->addWidget(pushSavePrezziEnergiaAs, 0, 1, 1, 1);

        pushLoadPrezziEnergia = new QPushButton(groupPrezzi);
        pushLoadPrezziEnergia->setObjectName(QString::fromUtf8("pushLoadPrezziEnergia"));

        gridLayout_9->addWidget(pushLoadPrezziEnergia, 0, 2, 1, 1);

        listEnergyPrices = new QListView(groupPrezzi);
        listEnergyPrices->setObjectName(QString::fromUtf8("listEnergyPrices"));
        listEnergyPrices->setMaximumSize(QSize(16777158, 16777215));
        listEnergyPrices->setAutoFillBackground(true);
        listEnergyPrices->setStyleSheet(QString::fromUtf8(" QListView {\n"
"     show-decoration-selected: 1; /* make the selection span the entire width of the view */\n"
" }\n"
"\n"
" QListView::item:alternate {\n"
"     background: #EEEEEE;\n"
" } QListView {\n"
"     alternate-background-color: yellow;\n"
" } QListView::item:selected {\n"
"     border: 1px solid #6a6ea9;\n"
" }\n"
"\n"
" QListView::item:selected:!active {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #ABAFE5, stop: 1 #8588B2);\n"
" }\n"
"\n"
" QListView::item:selected:active {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #6a6ea9, stop: 1 #888dd9);\n"
" }\n"
"\n"
" QListView::item:hover {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                 stop: 0 #FAFBFE, stop: 1 #DCDEF1);\n"
" }"));
        listEnergyPrices->setFrameShape(QFrame::Panel);
        listEnergyPrices->setFrameShadow(QFrame::Plain);

        gridLayout_9->addWidget(listEnergyPrices, 1, 0, 1, 3);


        gridLayout_14->addLayout(gridLayout_9, 0, 1, 2, 1);

        qwtPrezzi = new QwtPlot(groupPrezzi);
        qwtPrezzi->setObjectName(QString::fromUtf8("qwtPrezzi"));

        gridLayout_14->addWidget(qwtPrezzi, 0, 2, 2, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_10 = new QLabel(groupPrezzi);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);

        dAREnergyRate = new QDoubleSpinBox(groupPrezzi);
        dAREnergyRate->setObjectName(QString::fromUtf8("dAREnergyRate"));
        dAREnergyRate->setMaximum(100);

        horizontalLayout_4->addWidget(dAREnergyRate);


        gridLayout_14->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_17->addWidget(groupPrezzi, 1, 0, 1, 1);

        tabWidget->addTab(tabPrezzi, QString());
        tabEconomici = new QWidget();
        tabEconomici->setObjectName(QString::fromUtf8("tabEconomici"));
        gridLayout_19 = new QGridLayout(tabEconomici);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        groupBox_3 = new QGroupBox(tabEconomici);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_18 = new QGridLayout(groupBox_3);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        comboRegime = new QComboBox(groupBox_3);
        comboRegime->setObjectName(QString::fromUtf8("comboRegime"));

        gridLayout_18->addWidget(comboRegime, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(374, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_2, 0, 1, 1, 3);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_18->addWidget(label, 1, 0, 1, 1);

        dARCH = new QDoubleSpinBox(groupBox_3);
        dARCH->setObjectName(QString::fromUtf8("dARCH"));
        dARCH->setDecimals(4);
        dARCH->setMaximum(100);
        dARCH->setSingleStep(0.0001);

        gridLayout_18->addWidget(dARCH, 1, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(373, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_7, 1, 4, 1, 1);

        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_18->addWidget(label_24, 2, 0, 1, 2);

        dMinEnergyPrice = new QDoubleSpinBox(groupBox_3);
        dMinEnergyPrice->setObjectName(QString::fromUtf8("dMinEnergyPrice"));

        gridLayout_18->addWidget(dMinEnergyPrice, 2, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(379, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_3, 2, 4, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_18->addWidget(label_14, 3, 0, 1, 1);

        dIncentivi = new QDoubleSpinBox(groupBox_3);
        dIncentivi->setObjectName(QString::fromUtf8("dIncentivi"));
        dIncentivi->setMaximum(10000);
        dIncentivi->setSingleStep(0);

        gridLayout_18->addWidget(dIncentivi, 3, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(509, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_18->addItem(horizontalSpacer_6, 3, 3, 1, 2);


        gridLayout_19->addWidget(groupBox_3, 0, 0, 1, 3);

        label_20 = new QLabel(tabEconomici);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_19->addWidget(label_20, 1, 0, 1, 1);

        groupBox = new QGroupBox(tabEconomici);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8(" \n"
"\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 0, 0, 1, 1);

        dManutenzioneAnno = new QDoubleSpinBox(groupBox);
        dManutenzioneAnno->setObjectName(QString::fromUtf8("dManutenzioneAnno"));
        dManutenzioneAnno->setMaximum(20000);

        gridLayout_2->addWidget(dManutenzioneAnno, 0, 1, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 1, 0, 1, 1);

        dTasse = new QDoubleSpinBox(groupBox);
        dTasse->setObjectName(QString::fromUtf8("dTasse"));
        dTasse->setMaximum(20000);

        gridLayout_2->addWidget(dTasse, 1, 1, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 2, 0, 1, 1);

        dAffitti = new QDoubleSpinBox(groupBox);
        dAffitti->setObjectName(QString::fromUtf8("dAffitti"));

        gridLayout_2->addWidget(dAffitti, 2, 1, 1, 1);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 3, 0, 1, 1);

        dAltro = new QDoubleSpinBox(groupBox);
        dAltro->setObjectName(QString::fromUtf8("dAltro"));

        gridLayout_2->addWidget(dAltro, 3, 1, 1, 1);


        gridLayout_19->addWidget(groupBox, 1, 1, 1, 2);

        groupBox_2 = new QGroupBox(tabEconomici);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }\n"
"QGroupBox {\n"
"      \n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }"));
        gridLayout_10 = new QGridLayout(groupBox_2);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_10->addWidget(label_27, 0, 0, 1, 1);

        dCostoIniziale = new QDoubleSpinBox(groupBox_2);
        dCostoIniziale->setObjectName(QString::fromUtf8("dCostoIniziale"));
        dCostoIniziale->setMaximum(1e+09);

        gridLayout_10->addWidget(dCostoIniziale, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout_2->addWidget(label_28);

        dFinanziamento = new QDoubleSpinBox(groupBox_2);
        dFinanziamento->setObjectName(QString::fromUtf8("dFinanziamento"));
        dFinanziamento->setMaximum(1e+09);

        horizontalLayout_2->addWidget(dFinanziamento);

        dFinAnni = new QDoubleSpinBox(groupBox_2);
        dFinAnni->setObjectName(QString::fromUtf8("dFinAnni"));

        horizontalLayout_2->addWidget(dFinAnni);

        label_29 = new QLabel(groupBox_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        horizontalLayout_2->addWidget(label_29);


        gridLayout_10->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 0, 0, 1, 1);

        dTassoInflazione = new QDoubleSpinBox(groupBox_2);
        dTassoInflazione->setObjectName(QString::fromUtf8("dTassoInflazione"));
        dTassoInflazione->setMaximum(100);

        gridLayout_3->addWidget(dTassoInflazione, 0, 1, 1, 1);

        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_3->addWidget(label_19, 1, 0, 1, 1);

        dEnergyInflationRate = new QDoubleSpinBox(groupBox_2);
        dEnergyInflationRate->setObjectName(QString::fromUtf8("dEnergyInflationRate"));
        dEnergyInflationRate->setMaximum(100);

        gridLayout_3->addWidget(dEnergyInflationRate, 1, 1, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_3->addWidget(label_16, 2, 0, 1, 1);

        dLoanInterestRate = new QDoubleSpinBox(groupBox_2);
        dLoanInterestRate->setObjectName(QString::fromUtf8("dLoanInterestRate"));
        dLoanInterestRate->setMaximum(100);

        gridLayout_3->addWidget(dLoanInterestRate, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 3, 0, 1, 1);

        dDisscountRate = new QDoubleSpinBox(groupBox_2);
        dDisscountRate->setObjectName(QString::fromUtf8("dDisscountRate"));
        dDisscountRate->setMaximum(100);

        gridLayout_3->addWidget(dDisscountRate, 3, 1, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_3->addWidget(label_18, 4, 0, 1, 1);

        dPeriodo = new QDoubleSpinBox(groupBox_2);
        dPeriodo->setObjectName(QString::fromUtf8("dPeriodo"));

        gridLayout_3->addWidget(dPeriodo, 4, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_3, 2, 0, 1, 2);


        gridLayout_19->addWidget(groupBox_2, 2, 1, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 180, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_19->addItem(verticalSpacer_3, 3, 0, 1, 2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_5);

        pushSave_3 = new QPushButton(tabEconomici);
        pushSave_3->setObjectName(QString::fromUtf8("pushSave_3"));

        horizontalLayout_12->addWidget(pushSave_3);

        pushLoad_3 = new QPushButton(tabEconomici);
        pushLoad_3->setObjectName(QString::fromUtf8("pushLoad_3"));

        horizontalLayout_12->addWidget(pushLoad_3);


        gridLayout_19->addLayout(horizontalLayout_12, 4, 2, 1, 1);

        tabWidget->addTab(tabEconomici, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_12 = new QGridLayout(tab_2);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        qwtVan = new QwtPlot(tab_2);
        qwtVan->setObjectName(QString::fromUtf8("qwtVan"));

        gridLayout_12->addWidget(qwtVan, 0, 0, 1, 1);

        qwtPlot = new QwtPlot(tab_2);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));

        gridLayout_12->addWidget(qwtPlot, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout_3->addWidget(tabWidget);

        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        verticalLayout_2->addWidget(stackedWidget);


        retranslateUi(widgetEcoVal);

        stackedWidget->setCurrentIndex(0);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(widgetEcoVal);
    } // setupUi

    void retranslateUi(QWidget *widgetEcoVal)
    {
        widgetEcoVal->setWindowTitle(QApplication::translate("widgetEcoVal", "Form", 0, QApplication::UnicodeUTF8));
        groupBands->setTitle(QApplication::translate("widgetEcoVal", "Valori orari", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("widgetEcoVal", "Da", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("widgetEcoVal", "A", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("widgetEcoVal", "c/kWh", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("widgetEcoVal", "Denominazione", 0, QApplication::UnicodeUTF8));
        comboBands->clear();
        comboBands->insertItems(0, QStringList()
         << QApplication::translate("widgetEcoVal", "F1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F1 (sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F2 (sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F3 (sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F1 (domenica)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F2 (domenica)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "F3 (domenica)", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QString());
        label_3->setText(QString());
        pushSaveBandsAs->setText(QApplication::translate("widgetEcoVal", "Salva come", 0, QApplication::UnicodeUTF8));
        pushSaveBands->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
        pushLoadBands->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("widgetEcoVal", "Fasce orarie", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("widgetEcoVal", "TariffeTrasmissione", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("widgetEcoVal", " (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("widgetEcoVal", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Per i clienti italiani in modalit\303\240 SSP, le tariffe A,UC,MCT sono considerate tariffe per oneri generali. Per clienti domestici, le tariffe di Trasmissione, Distribuzione e Misura sono accorpate nelle cosiddette tariffe D2 e D3, a seconda della potenza installata. </p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Le tariffe D2 e D3 prevedono due tipi di costo: uno variabile per kWh e uno fisso per kW. Quindi, usare solo le Tariffe Distribuzione e Misura per inserire i val"
                        "ori.</p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Per i valori aggiornati, consultare il sito <a href=\"http://www.autorita.energia.it/elettricita/schede/auc_08.htm\"><span style=\" text-decoration: underline; color:#0000ff;\">AEEG</span></a></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; text-decoration: underline; color:#0000ff;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("widgetEcoVal", "TariffeDistribuzione", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("widgetEcoVal", " (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("widgetEcoVal", " (c/kW)", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("widgetEcoVal", " (c/anno)", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("widgetEcoVal", "Coefficienti per produttori", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("widgetEcoVal", "Perdita Trasmisisone(%)", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("widgetEcoVal", "Perdita Distribuzione(%)", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("widgetEcoVal", "CTR(c/kWh)", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("widgetEcoVal", "Altri costi (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("widgetEcoVal", "Altri costi mensili", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("widgetEcoVal", "Tariffe Misura", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("widgetEcoVal", " (c/anno)", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("widgetEcoVal", " (c/kWh)", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("widgetEcoVal", "Tariffe generali", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("widgetEcoVal", "(c/kWh)", 0, QApplication::UnicodeUTF8));
        pushSavePrezzi->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
        pushSavePrezziAs->setText(QApplication::translate("widgetEcoVal", "Salva come..", 0, QApplication::UnicodeUTF8));
        pushLoadPrezzi->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
        groupPrezzi->setTitle(QApplication::translate("widgetEcoVal", "Prezzi energia immessa", 0, QApplication::UnicodeUTF8));
        pushSavePrezziEnergia->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
        pushSavePrezziEnergiaAs->setText(QApplication::translate("widgetEcoVal", "Salva come", 0, QApplication::UnicodeUTF8));
        pushLoadPrezziEnergia->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("widgetEcoVal", "Coeff. AR.(%)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabPrezzi), QApplication::translate("widgetEcoVal", "Costi energia", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("widgetEcoVal", "Regime", 0, QApplication::UnicodeUTF8));
        comboRegime->clear();
        comboRegime->insertItems(0, QStringList()
         << QApplication::translate("widgetEcoVal", "Vendita", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "SSP Italia 2009", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "Semplice Scambio", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("widgetEcoVal", "Coefficiente. ARCH(%)", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("widgetEcoVal", "Prezzo minimo garantito(c/kWh)", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("widgetEcoVal", "Incentivi (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_20->setText(QString());
        groupBox->setTitle(QApplication::translate("widgetEcoVal", "Costi fissi", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("widgetEcoVal", "Manutenzione annuale", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("widgetEcoVal", "Tasse ", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("widgetEcoVal", "Affitti/anno", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("widgetEcoVal", "Altro", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("widgetEcoVal", "Variabili di investimento", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("widgetEcoVal", "Costo iniziale", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("widgetEcoVal", "Finanziamento", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("widgetEcoVal", "anni", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("widgetEcoVal", "Tasso inflazione(%)", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("widgetEcoVal", "Tasso inflazione Energia(%)", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("widgetEcoVal", "Tasso interesse Finanziamento(%)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("widgetEcoVal", "Tasso interesse Investimento(%)", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("widgetEcoVal", "Periodo d'analisi", 0, QApplication::UnicodeUTF8));
        pushSave_3->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
        pushLoad_3->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabEconomici), QApplication::translate("widgetEcoVal", "Aspetti economici", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("widgetEcoVal", "Flussi di Cassa", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(widgetEcoVal);
    } // retranslateUi

};

namespace Ui {
    class widgetEcoVal: public Ui_widgetEcoVal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ECOVAL_H
