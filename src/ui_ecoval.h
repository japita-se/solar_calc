/********************************************************************************
** Form generated from reading UI file 'ecoval.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECOVAL_H
#define UI_ECOVAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_widgetEcoVal
{
public:
    QGridLayout *gridLayout_23;
    QTreeWidget *treeWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_26;
    QGroupBox *groupBands;
    QGridLayout *gridLayout_34;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_7;
    QSpinBox *spinDa;
    QDoubleSpinBox *dValue;
    QPushButton *pushClearAllBands;
    QPushButton *pushUndo;
    QLabel *label_76;
    QComboBox *comboIntervals;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushAddConsumo;
    QComboBox *comboBands;
    QSpinBox *spinA;
    QLabel *label_6;
    QGridLayout *gridLayout_16;
    QSpacerItem *horizontalSpacer_6;
    QTableWidget *tableBandsView;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_28;
    QLabel *label_81;
    QDoubleSpinBox *dVATonEn;
    QLabel *label_82;
    QDoubleSpinBox *dIMPkWh;
    QwtPlot *qwtBands;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_66;
    QDoubleSpinBox *dBandsInflationRate;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_13;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushCutBandFile;
    QPushButton *pushSaveBandsAs;
    QPushButton *pushSaveBands;
    QPushButton *pushLoadBands;
    QPushButton *pushInfoBands;
    QListView *listBands;
    QLabel *label_4;
    QLabel *label_3;
    QWidget *page_2;
    QGridLayout *gridLayout_30;
    QGroupBox *groupTariffe;
    QGridLayout *gridLayout_27;
    QGridLayout *gridLayout_6;
    QLabel *label_32;
    QDoubleSpinBox *dLoss;
    QLabel *label_77;
    QComboBox *comboTariffeIntervals;
    QPushButton *pushTariffeIntervals;
    QGroupBox *groupTras;
    QGridLayout *gridLayout_5;
    QLabel *label_23;
    QDoubleSpinBox *dTrasmissionekWh;
    QLabel *label_46;
    QDoubleSpinBox *dTrasmissionekW;
    QLabel *label_54;
    QDoubleSpinBox *dTrasmissioneAnno;
    QGroupBox *groupDist;
    QGridLayout *gridLayout_4;
    QLabel *label_21;
    QDoubleSpinBox *dDistribuzionekWh;
    QLabel *label_25;
    QDoubleSpinBox *dDistribuzionekW;
    QLabel *label_26;
    QDoubleSpinBox *dDistribuzioneAnno;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_22;
    QLabel *label_30;
    QDoubleSpinBox *dMisurakWh;
    QLabel *label_63;
    QDoubleSpinBox *dMisurakW;
    QLabel *label_64;
    QDoubleSpinBox *dMisuraAnno;
    QGroupBox *groupDisp;
    QGridLayout *gridLayout_15;
    QLabel *label_61;
    QDoubleSpinBox *dDISPkWh;
    QLabel *label_62;
    QDoubleSpinBox *dDISPkW;
    QLabel *label_60;
    QDoubleSpinBox *dDISP;
    QGroupBox *groupGenerali;
    QGridLayout *gridLayout_32;
    QLabel *label_9;
    QDoubleSpinBox *dAUCkWh;
    QLabel *label_12;
    QDoubleSpinBox *dAUCkW;
    QLabel *label_22;
    QDoubleSpinBox *dAUCanno;
    QLabel *label_78;
    QDoubleSpinBox *dMCTkWh;
    QGroupBox *groupCoeffVendita;
    QGridLayout *gridLayout_8;
    QLabel *label_31;
    QDoubleSpinBox *dPerditaTrasmissione;
    QLabel *label_34;
    QDoubleSpinBox *dCTRkWh;
    QLabel *label_36;
    QLabel *label_35;
    QDoubleSpinBox *dAltriCostiMensili;
    QDoubleSpinBox *dCostiAmm;
    QLabel *label_79;
    QLabel *label_80;
    QDoubleSpinBox *dLimitCostiAmm;
    QDoubleSpinBox *dFattCTR;
    QLabel *label_56;
    QGridLayout *gridLayout_7;
    QListView *listTariffe;
    QPushButton *pushCutOneriFile;
    QPushButton *pushSavePrezziAs;
    QPushButton *pushSavePrezzi;
    QPushButton *pushLoadPrezzi;
    QPushButton *pushInfoTariffe;
    QLabel *label_65;
    QSpacerItem *horizontalSpacer;
    QWidget *page_3;
    QGridLayout *gridLayout_29;
    QGroupBox *groupPrezzi;
    QLabel *labelWarn;
    QGridLayout *gridLayout_9;
    QLabel *label_51;
    QComboBox *comboImmBand;
    QLabel *label_10;
    QTableWidget *tablePrezziEnergia;
    QTableWidget *tableSummaryBands;
    QLabel *label_40;
    QDoubleSpinBox *dEnergyInflationRate2;
    QGridLayout *gridLayout_17;
    QRadioButton *radioSimpleInflation;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout_14;
    QLabel *label_50;
    QListView *listEnergyPrices;
    QPushButton *pushCutPrezziFile;
    QPushButton *pushSavePrezziEnergiaAs;
    QPushButton *pushSavePrezziEnergia;
    QPushButton *pushLoadPrezziEnergia;
    QPushButton *pushInfoPrezzi;
    QSpacerItem *horizontalSpacer_5;
    QWidget *page_5;
    QGridLayout *gridLayout_37;
    QGroupBox *groupMinPrices;
    QGridLayout *gridLayout_36;
    QCheckBox *checkImmIntervals;
    QwtPlot *qwtMinPrezzi;
    QGroupBox *groupImmIntervals;
    QGridLayout *gridLayout_25;
    QComboBox *comboImmissione;
    QPushButton *pushImmissione;
    QLabel *label_33;
    QDoubleSpinBox *dYearlyMinPrice;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_35;
    QTableWidget *tableMinPrezziEnergia;
    QGridLayout *gridLayout_18;
    QRadioButton *radioGARCH_2;
    QLabel *label_41;
    QDoubleSpinBox *dminPricesA1;
    QLabel *label_42;
    QDoubleSpinBox *dminPricesB1;
    QLabel *label_43;
    QDoubleSpinBox *dminPricesO1;
    QLabel *label_44;
    QDoubleSpinBox *dminPricesMu;
    QSpacerItem *verticalSpacer_3;
    QGridLayout *gridLayout_19;
    QRadioButton *radioSimpleInflation_2;
    QLabel *label_45;
    QDoubleSpinBox *dEnergyInflationRateSell;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBoxPM;
    QGridLayout *gridLayout_33;
    QGridLayout *gridLayout_20;
    QListView *listMinEnergyPrices;
    QPushButton *pushCutMinPrezziFile;
    QPushButton *pushSaveMinPrezziEnergiaAs;
    QPushButton *pushSaveMinPrezziEnergia;
    QPushButton *pushLoadMinPrezziEnergia;
    QPushButton *pushInfoPrezziMinimi;
    QSpacerItem *horizontalSpacer_4;
    QLabel *labelWarnMin;
    QWidget *page_4;
    QGridLayout *gridLayout_38;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_10;
    QComboBox *comboRegime;
    QCheckBox *checkCredit;
    QLabel *label_58;
    QDoubleSpinBox *dPotenzakW;
    QLabel *label_59;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *label_27;
    QDoubleSpinBox *dCostoIniziale;
    QLabel *label_14;
    QDoubleSpinBox *dIncentivi;
    QSpinBox *dBonusesYears;
    QLabel *label_57;
    QLabel *label_52;
    QDoubleSpinBox *dVAT;
    QLabel *label_20;
    QDoubleSpinBox *dIncentiviPerkWp;
    QLabel *label_28;
    QDoubleSpinBox *dFinanziamento;
    QSpinBox *dFinAnni;
    QLabel *label_29;
    QLabel *label_84;
    QLabel *label_15;
    QDoubleSpinBox *dTassoInflazione;
    QLabel *label_16;
    QDoubleSpinBox *dLoanInterestRate;
    QLabel *label_2;
    QDoubleSpinBox *dDiscountRate;
    QLabel *label_18;
    QSpinBox *dPeriodo;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_12;
    QLabel *label_11;
    QDoubleSpinBox *dManutenzioneAnno;
    QLabel *label_47;
    QDoubleSpinBox *dManutenzioneS;
    QLabel *label_48;
    QSpinBox *dManutenzioneSFreq;
    QLabel *label_13;
    QDoubleSpinBox *dAffitti;
    QLabel *label_17;
    QDoubleSpinBox *dAltro;
    QLabel *label_19;
    QDoubleSpinBox *dAssicurazione;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_55;
    QSpinBox *dAssicurazioneAnni;
    QSpacerItem *verticalSpacer_6;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_2;
    QLabel *label_24;
    QDoubleSpinBox *dTaxReductionInterest;
    QLabel *label;
    QDoubleSpinBox *dTaxReduction;
    QDoubleSpinBox *dTaxReductionVAT;
    QLabel *label_53;
    QDoubleSpinBox *dAmmortamento;
    QLabel *label_49;
    QDoubleSpinBox *dReductionInitialCost;
    QLabel *label_83;
    QWidget *page_7;
    QGridLayout *gridLayout_31;
    QGroupBox *groupTax;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_24;
    QLabel *label_67;
    QLabel *label_68;
    QLabel *label_69;
    QLabel *label_70;
    QDoubleSpinBox *dTIvaBonus;
    QDoubleSpinBox *dTIvaCS;
    QDoubleSpinBox *dTIvaEn;
    QLabel *label_71;
    QDoubleSpinBox *dTIrpefBonus;
    QDoubleSpinBox *dTIrpefCS;
    QDoubleSpinBox *dTIrpefEn;
    QLabel *label_72;
    QDoubleSpinBox *dTIrapBonus;
    QDoubleSpinBox *dTIrapCS;
    QDoubleSpinBox *dTIrapEn;
    QLabel *label_73;
    QDoubleSpinBox *dTIresBonus;
    QDoubleSpinBox *dTIresCS;
    QDoubleSpinBox *dTIresEn;
    QDoubleSpinBox *dTAltroEn;
    QDoubleSpinBox *dTAltroCS;
    QDoubleSpinBox *dTAltroBonus;
    QLabel *label_75;
    QVBoxLayout *verticalLayout;
    QLabel *label_74;
    QListView *listTaxes;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushCutTaxFile;
    QPushButton *pushSaveTax;
    QPushButton *pushSaveTaxAs;
    QPushButton *pushLoadTax;
    QPushButton *pushInfoTax;
    QSpacerItem *verticalSpacer_10;
    QWidget *page_6;

    void setupUi(QWidget *widgetEcoVal)
    {
        if (widgetEcoVal->objectName().isEmpty())
            widgetEcoVal->setObjectName(QString::fromUtf8("widgetEcoVal"));
        widgetEcoVal->resize(1073, 968);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetEcoVal->sizePolicy().hasHeightForWidth());
        widgetEcoVal->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/ecopara.png"), QSize(), QIcon::Normal, QIcon::Off);
        widgetEcoVal->setWindowIcon(icon);
        gridLayout_23 = new QGridLayout(widgetEcoVal);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        treeWidget = new QTreeWidget(widgetEcoVal);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(treeWidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setMinimumSize(QSize(220, 0));
        treeWidget->setStyleSheet(QString::fromUtf8("QTreeWidget {\n"
"     alternate-background-color: yellow;\n"
"     background: burlywood;\n"
"margin-left:-15px\n"
"	\n"
" }\n"
"QTreeWidget {\n"
"     show-decoration-selected: 1;\n"
" }\n"
"\n"
" QTreeWidget::item {\n"
"      border: 0px solid #d9d9d9;\n"
"     border-top-color: transparent;\n"
"     border-bottom-color: transparent;\n"
" }\n"
"\n"
" QTreeWidget::item:hover {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e8effd, stop: 1 #cbdaf1);\n"
"     border: 1px solid #bfcde4;\n"
" }\n"
"\n"
" QTreeView::item:selected {\n"
"     border: 0px solid #567dbc;\n"
" }\n"
"\n"
" QTreeWidget::item:selected:active{\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);\n"
" }\n"
"\n"
" QTreeWidget::item:selected:!active {\n"
"     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);\n"
" }\n"
""));
        treeWidget->setColumnCount(1);
        treeWidget->header()->setVisible(false);

        gridLayout_23->addWidget(treeWidget, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(widgetEcoVal);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_26 = new QGridLayout(page);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        groupBands = new QGroupBox(page);
        groupBands->setObjectName(QString::fromUtf8("groupBands"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBands->sizePolicy().hasHeightForWidth());
        groupBands->setSizePolicy(sizePolicy3);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        groupBands->setFont(font);
        groupBands->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 2px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_34 = new QGridLayout(groupBands);
        gridLayout_34->setObjectName(QString::fromUtf8("gridLayout_34"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(groupBands);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        label_7 = new QLabel(groupBands);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 3, 1, 1);

        spinDa = new QSpinBox(groupBands);
        spinDa->setObjectName(QString::fromUtf8("spinDa"));
        spinDa->setMaximum(23);

        gridLayout->addWidget(spinDa, 0, 4, 1, 1);

        dValue = new QDoubleSpinBox(groupBands);
        dValue->setObjectName(QString::fromUtf8("dValue"));
        dValue->setDecimals(4);
        dValue->setMaximum(10000);

        gridLayout->addWidget(dValue, 0, 8, 1, 1);

        pushClearAllBands = new QPushButton(groupBands);
        pushClearAllBands->setObjectName(QString::fromUtf8("pushClearAllBands"));

        gridLayout->addWidget(pushClearAllBands, 0, 10, 1, 1);

        pushUndo = new QPushButton(groupBands);
        pushUndo->setObjectName(QString::fromUtf8("pushUndo"));

        gridLayout->addWidget(pushUndo, 0, 11, 1, 1);

        label_76 = new QLabel(groupBands);
        label_76->setObjectName(QString::fromUtf8("label_76"));
        label_76->setWordWrap(true);

        gridLayout->addWidget(label_76, 1, 0, 2, 1);

        comboIntervals = new QComboBox(groupBands);
        comboIntervals->setObjectName(QString::fromUtf8("comboIntervals"));

        gridLayout->addWidget(comboIntervals, 2, 1, 1, 3);

        label_8 = new QLabel(groupBands);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 9, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 2, 5, 1, 1);

        pushAddConsumo = new QPushButton(groupBands);
        pushAddConsumo->setObjectName(QString::fromUtf8("pushAddConsumo"));
        pushAddConsumo->setMaximumSize(QSize(30, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushAddConsumo->setIcon(icon1);

        gridLayout->addWidget(pushAddConsumo, 2, 4, 1, 1);

        comboBands = new QComboBox(groupBands);
        comboBands->setObjectName(QString::fromUtf8("comboBands"));

        gridLayout->addWidget(comboBands, 0, 1, 1, 1);

        spinA = new QSpinBox(groupBands);
        spinA->setObjectName(QString::fromUtf8("spinA"));
        spinA->setMaximum(23);

        gridLayout->addWidget(spinA, 0, 7, 1, 1);

        label_6 = new QLabel(groupBands);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 6, 1, 1);


        gridLayout_34->addLayout(gridLayout, 0, 1, 1, 2);

        gridLayout_16 = new QGridLayout();
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_16->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        tableBandsView = new QTableWidget(groupBands);
        if (tableBandsView->columnCount() < 24)
            tableBandsView->setColumnCount(24);
        if (tableBandsView->rowCount() < 12)
            tableBandsView->setRowCount(12);
        tableBandsView->setObjectName(QString::fromUtf8("tableBandsView"));
        tableBandsView->setMinimumSize(QSize(0, 0));
        tableBandsView->setFrameShape(QFrame::Panel);
        tableBandsView->setFrameShadow(QFrame::Sunken);
        tableBandsView->setAlternatingRowColors(true);
        tableBandsView->setGridStyle(Qt::DotLine);
        tableBandsView->setRowCount(12);
        tableBandsView->setColumnCount(24);
        tableBandsView->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableBandsView->horizontalHeader()->setStretchLastSection(false);

        gridLayout_16->addWidget(tableBandsView, 1, 0, 1, 2);


        gridLayout_34->addLayout(gridLayout_16, 1, 0, 1, 3);

        groupBox_10 = new QGroupBox(groupBands);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_10->sizePolicy().hasHeightForWidth());
        groupBox_10->setSizePolicy(sizePolicy4);
        groupBox_10->setMaximumSize(QSize(16777215, 100));
        groupBox_10->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
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
        gridLayout_28 = new QGridLayout(groupBox_10);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        label_81 = new QLabel(groupBox_10);
        label_81->setObjectName(QString::fromUtf8("label_81"));

        gridLayout_28->addWidget(label_81, 1, 0, 1, 1);

        dVATonEn = new QDoubleSpinBox(groupBox_10);
        dVATonEn->setObjectName(QString::fromUtf8("dVATonEn"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(dVATonEn->sizePolicy().hasHeightForWidth());
        dVATonEn->setSizePolicy(sizePolicy5);
        dVATonEn->setDecimals(4);
        dVATonEn->setMaximum(100);

        gridLayout_28->addWidget(dVATonEn, 1, 1, 1, 1);

        label_82 = new QLabel(groupBox_10);
        label_82->setObjectName(QString::fromUtf8("label_82"));

        gridLayout_28->addWidget(label_82, 2, 0, 1, 1);

        dIMPkWh = new QDoubleSpinBox(groupBox_10);
        dIMPkWh->setObjectName(QString::fromUtf8("dIMPkWh"));
        sizePolicy5.setHeightForWidth(dIMPkWh->sizePolicy().hasHeightForWidth());
        dIMPkWh->setSizePolicy(sizePolicy5);
        dIMPkWh->setDecimals(4);
        dIMPkWh->setMaximum(2e+06);

        gridLayout_28->addWidget(dIMPkWh, 2, 1, 1, 1);


        gridLayout_34->addWidget(groupBox_10, 4, 0, 1, 2);

        qwtBands = new QwtPlot(groupBands);
        qwtBands->setObjectName(QString::fromUtf8("qwtBands"));
        sizePolicy3.setHeightForWidth(qwtBands->sizePolicy().hasHeightForWidth());
        qwtBands->setSizePolicy(sizePolicy3);
        qwtBands->setMaximumSize(QSize(16777215, 500));

        gridLayout_34->addWidget(qwtBands, 4, 2, 5, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_66 = new QLabel(groupBands);
        label_66->setObjectName(QString::fromUtf8("label_66"));

        horizontalLayout_2->addWidget(label_66);

        dBandsInflationRate = new QDoubleSpinBox(groupBands);
        dBandsInflationRate->setObjectName(QString::fromUtf8("dBandsInflationRate"));
        sizePolicy5.setHeightForWidth(dBandsInflationRate->sizePolicy().hasHeightForWidth());
        dBandsInflationRate->setSizePolicy(sizePolicy5);
        dBandsInflationRate->setDecimals(4);
        dBandsInflationRate->setMaximum(100);

        horizontalLayout_2->addWidget(dBandsInflationRate);


        gridLayout_34->addLayout(horizontalLayout_2, 6, 0, 2, 2);

        groupBox_11 = new QGroupBox(groupBands);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(groupBox_11->sizePolicy().hasHeightForWidth());
        groupBox_11->setSizePolicy(sizePolicy6);
        groupBox_11->setMinimumSize(QSize(0, 0));
        groupBox_11->setMaximumSize(QSize(400, 200));
        groupBox_11->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_13 = new QGridLayout(groupBox_11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushCutBandFile = new QPushButton(groupBox_11);
        pushCutBandFile->setObjectName(QString::fromUtf8("pushCutBandFile"));

        horizontalLayout->addWidget(pushCutBandFile);

        pushSaveBandsAs = new QPushButton(groupBox_11);
        pushSaveBandsAs->setObjectName(QString::fromUtf8("pushSaveBandsAs"));

        horizontalLayout->addWidget(pushSaveBandsAs);

        pushSaveBands = new QPushButton(groupBox_11);
        pushSaveBands->setObjectName(QString::fromUtf8("pushSaveBands"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushSaveBands->setIcon(icon2);

        horizontalLayout->addWidget(pushSaveBands);

        pushLoadBands = new QPushButton(groupBox_11);
        pushLoadBands->setObjectName(QString::fromUtf8("pushLoadBands"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushLoadBands->setIcon(icon3);

        horizontalLayout->addWidget(pushLoadBands);

        pushInfoBands = new QPushButton(groupBox_11);
        pushInfoBands->setObjectName(QString::fromUtf8("pushInfoBands"));

        horizontalLayout->addWidget(pushInfoBands);


        gridLayout_13->addLayout(horizontalLayout, 1, 0, 1, 1);

        listBands = new QListView(groupBox_11);
        listBands->setObjectName(QString::fromUtf8("listBands"));
        sizePolicy6.setHeightForWidth(listBands->sizePolicy().hasHeightForWidth());
        listBands->setSizePolicy(sizePolicy6);
        listBands->setMinimumSize(QSize(144, 53));

        gridLayout_13->addWidget(listBands, 0, 0, 1, 1);


        gridLayout_34->addWidget(groupBox_11, 8, 1, 1, 1);

        label_4 = new QLabel(groupBands);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(90, 40));
        label_4->setWordWrap(true);

        gridLayout_34->addWidget(label_4, 2, 0, 1, 2);

        label_3 = new QLabel(groupBands);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(90, 18));
        label_3->setWordWrap(true);

        gridLayout_34->addWidget(label_3, 3, 0, 1, 2);


        gridLayout_26->addWidget(groupBands, 0, 1, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_30 = new QGridLayout(page_2);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        groupTariffe = new QGroupBox(page_2);
        groupTariffe->setObjectName(QString::fromUtf8("groupTariffe"));
        sizePolicy3.setHeightForWidth(groupTariffe->sizePolicy().hasHeightForWidth());
        groupTariffe->setSizePolicy(sizePolicy3);
        groupTariffe->setFont(font);
        groupTariffe->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_27 = new QGridLayout(groupTariffe);
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_32 = new QLabel(groupTariffe);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_6->addWidget(label_32, 0, 0, 1, 1);

        dLoss = new QDoubleSpinBox(groupTariffe);
        dLoss->setObjectName(QString::fromUtf8("dLoss"));
        dLoss->setDecimals(4);
        dLoss->setMinimum(1);
        dLoss->setMaximum(100);

        gridLayout_6->addWidget(dLoss, 0, 1, 1, 1);

        label_77 = new QLabel(groupTariffe);
        label_77->setObjectName(QString::fromUtf8("label_77"));
        label_77->setWordWrap(true);

        gridLayout_6->addWidget(label_77, 1, 0, 1, 1);

        comboTariffeIntervals = new QComboBox(groupTariffe);
        comboTariffeIntervals->setObjectName(QString::fromUtf8("comboTariffeIntervals"));

        gridLayout_6->addWidget(comboTariffeIntervals, 1, 1, 1, 1);

        pushTariffeIntervals = new QPushButton(groupTariffe);
        pushTariffeIntervals->setObjectName(QString::fromUtf8("pushTariffeIntervals"));
        pushTariffeIntervals->setMaximumSize(QSize(30, 16777215));
        pushTariffeIntervals->setIcon(icon1);

        gridLayout_6->addWidget(pushTariffeIntervals, 1, 2, 1, 1);


        gridLayout_27->addLayout(gridLayout_6, 0, 0, 1, 2);

        groupTras = new QGroupBox(groupTariffe);
        groupTras->setObjectName(QString::fromUtf8("groupTras"));
        sizePolicy4.setHeightForWidth(groupTras->sizePolicy().hasHeightForWidth());
        groupTras->setSizePolicy(sizePolicy4);
        groupTras->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
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
        gridLayout_5 = new QGridLayout(groupTras);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_23 = new QLabel(groupTras);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_5->addWidget(label_23, 0, 0, 1, 1);

        dTrasmissionekWh = new QDoubleSpinBox(groupTras);
        dTrasmissionekWh->setObjectName(QString::fromUtf8("dTrasmissionekWh"));
        dTrasmissionekWh->setDecimals(4);
        dTrasmissionekWh->setMaximum(1e+09);
        dTrasmissionekWh->setSingleStep(1);

        gridLayout_5->addWidget(dTrasmissionekWh, 0, 1, 1, 1);

        label_46 = new QLabel(groupTras);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout_5->addWidget(label_46, 1, 0, 1, 1);

        dTrasmissionekW = new QDoubleSpinBox(groupTras);
        dTrasmissionekW->setObjectName(QString::fromUtf8("dTrasmissionekW"));
        dTrasmissionekW->setDecimals(4);
        dTrasmissionekW->setMaximum(1e+09);
        dTrasmissionekW->setSingleStep(1);

        gridLayout_5->addWidget(dTrasmissionekW, 1, 1, 1, 1);

        label_54 = new QLabel(groupTras);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        gridLayout_5->addWidget(label_54, 2, 0, 1, 1);

        dTrasmissioneAnno = new QDoubleSpinBox(groupTras);
        dTrasmissioneAnno->setObjectName(QString::fromUtf8("dTrasmissioneAnno"));
        dTrasmissioneAnno->setDecimals(4);
        dTrasmissioneAnno->setMaximum(1e+09);
        dTrasmissioneAnno->setSingleStep(1);

        gridLayout_5->addWidget(dTrasmissioneAnno, 2, 1, 1, 1);


        gridLayout_27->addWidget(groupTras, 1, 0, 1, 1);

        groupDist = new QGroupBox(groupTariffe);
        groupDist->setObjectName(QString::fromUtf8("groupDist"));
        sizePolicy4.setHeightForWidth(groupDist->sizePolicy().hasHeightForWidth());
        groupDist->setSizePolicy(sizePolicy4);
        groupDist->setMinimumSize(QSize(200, 0));
        groupDist->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
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
        gridLayout_4 = new QGridLayout(groupDist);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_21 = new QLabel(groupDist);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_4->addWidget(label_21, 0, 0, 1, 1);

        dDistribuzionekWh = new QDoubleSpinBox(groupDist);
        dDistribuzionekWh->setObjectName(QString::fromUtf8("dDistribuzionekWh"));
        dDistribuzionekWh->setDecimals(4);
        dDistribuzionekWh->setMaximum(1e+09);
        dDistribuzionekWh->setSingleStep(1);

        gridLayout_4->addWidget(dDistribuzionekWh, 0, 1, 1, 1);

        label_25 = new QLabel(groupDist);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_4->addWidget(label_25, 1, 0, 1, 1);

        dDistribuzionekW = new QDoubleSpinBox(groupDist);
        dDistribuzionekW->setObjectName(QString::fromUtf8("dDistribuzionekW"));
        dDistribuzionekW->setDecimals(4);
        dDistribuzionekW->setMaximum(1e+09);

        gridLayout_4->addWidget(dDistribuzionekW, 1, 1, 1, 1);

        label_26 = new QLabel(groupDist);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_4->addWidget(label_26, 2, 0, 1, 1);

        dDistribuzioneAnno = new QDoubleSpinBox(groupDist);
        dDistribuzioneAnno->setObjectName(QString::fromUtf8("dDistribuzioneAnno"));
        dDistribuzioneAnno->setDecimals(4);
        dDistribuzioneAnno->setMaximum(1e+09);

        gridLayout_4->addWidget(dDistribuzioneAnno, 2, 1, 1, 1);


        gridLayout_27->addWidget(groupDist, 1, 1, 1, 2);

        groupBox_5 = new QGroupBox(groupTariffe);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy4.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy4);
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
        gridLayout_22 = new QGridLayout(groupBox_5);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        label_30 = new QLabel(groupBox_5);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_22->addWidget(label_30, 0, 0, 1, 1);

        dMisurakWh = new QDoubleSpinBox(groupBox_5);
        dMisurakWh->setObjectName(QString::fromUtf8("dMisurakWh"));
        dMisurakWh->setDecimals(4);
        dMisurakWh->setMaximum(1e+09);
        dMisurakWh->setSingleStep(1);

        gridLayout_22->addWidget(dMisurakWh, 0, 1, 1, 1);

        label_63 = new QLabel(groupBox_5);
        label_63->setObjectName(QString::fromUtf8("label_63"));

        gridLayout_22->addWidget(label_63, 1, 0, 1, 1);

        dMisurakW = new QDoubleSpinBox(groupBox_5);
        dMisurakW->setObjectName(QString::fromUtf8("dMisurakW"));
        dMisurakW->setDecimals(4);
        dMisurakW->setMaximum(1e+09);
        dMisurakW->setSingleStep(1);

        gridLayout_22->addWidget(dMisurakW, 1, 1, 1, 1);

        label_64 = new QLabel(groupBox_5);
        label_64->setObjectName(QString::fromUtf8("label_64"));

        gridLayout_22->addWidget(label_64, 2, 0, 1, 1);

        dMisuraAnno = new QDoubleSpinBox(groupBox_5);
        dMisuraAnno->setObjectName(QString::fromUtf8("dMisuraAnno"));
        dMisuraAnno->setDecimals(4);
        dMisuraAnno->setMaximum(1e+09);
        dMisuraAnno->setSingleStep(1);

        gridLayout_22->addWidget(dMisuraAnno, 2, 1, 1, 1);


        gridLayout_27->addWidget(groupBox_5, 1, 3, 1, 1);

        groupDisp = new QGroupBox(groupTariffe);
        groupDisp->setObjectName(QString::fromUtf8("groupDisp"));
        sizePolicy4.setHeightForWidth(groupDisp->sizePolicy().hasHeightForWidth());
        groupDisp->setSizePolicy(sizePolicy4);
        groupDisp->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
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
        gridLayout_15 = new QGridLayout(groupDisp);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        label_61 = new QLabel(groupDisp);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        gridLayout_15->addWidget(label_61, 0, 0, 1, 1);

        dDISPkWh = new QDoubleSpinBox(groupDisp);
        dDISPkWh->setObjectName(QString::fromUtf8("dDISPkWh"));
        dDISPkWh->setDecimals(4);
        dDISPkWh->setMaximum(1e+09);
        dDISPkWh->setSingleStep(1);

        gridLayout_15->addWidget(dDISPkWh, 0, 1, 1, 1);

        label_62 = new QLabel(groupDisp);
        label_62->setObjectName(QString::fromUtf8("label_62"));

        gridLayout_15->addWidget(label_62, 1, 0, 1, 1);

        dDISPkW = new QDoubleSpinBox(groupDisp);
        dDISPkW->setObjectName(QString::fromUtf8("dDISPkW"));
        dDISPkW->setDecimals(4);
        dDISPkW->setMaximum(1e+09);
        dDISPkW->setSingleStep(1);

        gridLayout_15->addWidget(dDISPkW, 1, 1, 1, 1);

        label_60 = new QLabel(groupDisp);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayout_15->addWidget(label_60, 2, 0, 1, 1);

        dDISP = new QDoubleSpinBox(groupDisp);
        dDISP->setObjectName(QString::fromUtf8("dDISP"));
        dDISP->setDecimals(4);
        dDISP->setMaximum(1e+09);

        gridLayout_15->addWidget(dDISP, 2, 1, 1, 1);


        gridLayout_27->addWidget(groupDisp, 2, 0, 1, 1);

        groupGenerali = new QGroupBox(groupTariffe);
        groupGenerali->setObjectName(QString::fromUtf8("groupGenerali"));
        sizePolicy4.setHeightForWidth(groupGenerali->sizePolicy().hasHeightForWidth());
        groupGenerali->setSizePolicy(sizePolicy4);
        groupGenerali->setMinimumSize(QSize(200, 0));
        groupGenerali->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
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
        gridLayout_32 = new QGridLayout(groupGenerali);
        gridLayout_32->setObjectName(QString::fromUtf8("gridLayout_32"));
        label_9 = new QLabel(groupGenerali);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_32->addWidget(label_9, 0, 0, 1, 1);

        dAUCkWh = new QDoubleSpinBox(groupGenerali);
        dAUCkWh->setObjectName(QString::fromUtf8("dAUCkWh"));
        sizePolicy5.setHeightForWidth(dAUCkWh->sizePolicy().hasHeightForWidth());
        dAUCkWh->setSizePolicy(sizePolicy5);
        dAUCkWh->setDecimals(4);
        dAUCkWh->setMaximum(1e+09);

        gridLayout_32->addWidget(dAUCkWh, 0, 1, 1, 1);

        label_12 = new QLabel(groupGenerali);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_32->addWidget(label_12, 1, 0, 1, 1);

        dAUCkW = new QDoubleSpinBox(groupGenerali);
        dAUCkW->setObjectName(QString::fromUtf8("dAUCkW"));
        sizePolicy5.setHeightForWidth(dAUCkW->sizePolicy().hasHeightForWidth());
        dAUCkW->setSizePolicy(sizePolicy5);
        dAUCkW->setDecimals(4);
        dAUCkW->setMaximum(1e+09);

        gridLayout_32->addWidget(dAUCkW, 1, 1, 1, 1);

        label_22 = new QLabel(groupGenerali);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_32->addWidget(label_22, 2, 0, 1, 1);

        dAUCanno = new QDoubleSpinBox(groupGenerali);
        dAUCanno->setObjectName(QString::fromUtf8("dAUCanno"));
        sizePolicy5.setHeightForWidth(dAUCanno->sizePolicy().hasHeightForWidth());
        dAUCanno->setSizePolicy(sizePolicy5);
        dAUCanno->setDecimals(6);
        dAUCanno->setMaximum(1e+09);

        gridLayout_32->addWidget(dAUCanno, 2, 1, 1, 1);

        label_78 = new QLabel(groupGenerali);
        label_78->setObjectName(QString::fromUtf8("label_78"));

        gridLayout_32->addWidget(label_78, 3, 0, 1, 1);

        dMCTkWh = new QDoubleSpinBox(groupGenerali);
        dMCTkWh->setObjectName(QString::fromUtf8("dMCTkWh"));
        dMCTkWh->setDecimals(4);
        dMCTkWh->setMaximum(1e+09);

        gridLayout_32->addWidget(dMCTkWh, 3, 1, 1, 1);


        gridLayout_27->addWidget(groupGenerali, 2, 1, 1, 2);

        groupCoeffVendita = new QGroupBox(groupTariffe);
        groupCoeffVendita->setObjectName(QString::fromUtf8("groupCoeffVendita"));
        sizePolicy3.setHeightForWidth(groupCoeffVendita->sizePolicy().hasHeightForWidth());
        groupCoeffVendita->setSizePolicy(sizePolicy3);
        groupCoeffVendita->setMaximumSize(QSize(16777215, 16777215));
        groupCoeffVendita->setStyleSheet(QString::fromUtf8("QGroupBox::title {\n"
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
        gridLayout_8 = new QGridLayout(groupCoeffVendita);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_31 = new QLabel(groupCoeffVendita);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_8->addWidget(label_31, 0, 0, 1, 1);

        dPerditaTrasmissione = new QDoubleSpinBox(groupCoeffVendita);
        dPerditaTrasmissione->setObjectName(QString::fromUtf8("dPerditaTrasmissione"));
        dPerditaTrasmissione->setDecimals(4);
        dPerditaTrasmissione->setMaximum(1e+09);

        gridLayout_8->addWidget(dPerditaTrasmissione, 0, 1, 1, 1);

        label_34 = new QLabel(groupCoeffVendita);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_8->addWidget(label_34, 3, 0, 1, 1);

        dCTRkWh = new QDoubleSpinBox(groupCoeffVendita);
        dCTRkWh->setObjectName(QString::fromUtf8("dCTRkWh"));
        dCTRkWh->setDecimals(4);
        dCTRkWh->setMaximum(1e+09);

        gridLayout_8->addWidget(dCTRkWh, 3, 1, 1, 1);

        label_36 = new QLabel(groupCoeffVendita);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setWordWrap(true);

        gridLayout_8->addWidget(label_36, 4, 0, 1, 1);

        label_35 = new QLabel(groupCoeffVendita);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_8->addWidget(label_35, 5, 0, 1, 1);

        dAltriCostiMensili = new QDoubleSpinBox(groupCoeffVendita);
        dAltriCostiMensili->setObjectName(QString::fromUtf8("dAltriCostiMensili"));
        sizePolicy5.setHeightForWidth(dAltriCostiMensili->sizePolicy().hasHeightForWidth());
        dAltriCostiMensili->setSizePolicy(sizePolicy5);
        dAltriCostiMensili->setDecimals(4);
        dAltriCostiMensili->setMaximum(1e+09);

        gridLayout_8->addWidget(dAltriCostiMensili, 5, 1, 1, 1);

        dCostiAmm = new QDoubleSpinBox(groupCoeffVendita);
        dCostiAmm->setObjectName(QString::fromUtf8("dCostiAmm"));
        dCostiAmm->setDecimals(4);
        dCostiAmm->setMaximum(100);

        gridLayout_8->addWidget(dCostiAmm, 1, 1, 1, 1);

        label_79 = new QLabel(groupCoeffVendita);
        label_79->setObjectName(QString::fromUtf8("label_79"));

        gridLayout_8->addWidget(label_79, 1, 0, 1, 1);

        label_80 = new QLabel(groupCoeffVendita);
        label_80->setObjectName(QString::fromUtf8("label_80"));

        gridLayout_8->addWidget(label_80, 2, 0, 1, 1);

        dLimitCostiAmm = new QDoubleSpinBox(groupCoeffVendita);
        dLimitCostiAmm->setObjectName(QString::fromUtf8("dLimitCostiAmm"));
        dLimitCostiAmm->setMaximum(1e+09);

        gridLayout_8->addWidget(dLimitCostiAmm, 2, 1, 1, 1);

        dFattCTR = new QDoubleSpinBox(groupCoeffVendita);
        dFattCTR->setObjectName(QString::fromUtf8("dFattCTR"));
        sizePolicy5.setHeightForWidth(dFattCTR->sizePolicy().hasHeightForWidth());
        dFattCTR->setSizePolicy(sizePolicy5);
        dFattCTR->setDecimals(4);
        dFattCTR->setMaximum(1e+09);

        gridLayout_8->addWidget(dFattCTR, 4, 1, 1, 1);


        gridLayout_27->addWidget(groupCoeffVendita, 2, 3, 1, 1);

        label_56 = new QLabel(groupTariffe);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        gridLayout_27->addWidget(label_56, 3, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        listTariffe = new QListView(groupTariffe);
        listTariffe->setObjectName(QString::fromUtf8("listTariffe"));
        listTariffe->setMaximumSize(QSize(10000, 300));
        listTariffe->setAutoFillBackground(true);
        listTariffe->setStyleSheet(QString::fromUtf8(" QListView {\n"
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
        listTariffe->setFrameShape(QFrame::Panel);
        listTariffe->setFrameShadow(QFrame::Plain);
        listTariffe->setWordWrap(true);

        gridLayout_7->addWidget(listTariffe, 0, 0, 1, 5);

        pushCutOneriFile = new QPushButton(groupTariffe);
        pushCutOneriFile->setObjectName(QString::fromUtf8("pushCutOneriFile"));

        gridLayout_7->addWidget(pushCutOneriFile, 1, 0, 1, 1);

        pushSavePrezziAs = new QPushButton(groupTariffe);
        pushSavePrezziAs->setObjectName(QString::fromUtf8("pushSavePrezziAs"));

        gridLayout_7->addWidget(pushSavePrezziAs, 1, 1, 1, 1);

        pushSavePrezzi = new QPushButton(groupTariffe);
        pushSavePrezzi->setObjectName(QString::fromUtf8("pushSavePrezzi"));
        pushSavePrezzi->setIcon(icon2);

        gridLayout_7->addWidget(pushSavePrezzi, 1, 2, 1, 1);

        pushLoadPrezzi = new QPushButton(groupTariffe);
        pushLoadPrezzi->setObjectName(QString::fromUtf8("pushLoadPrezzi"));
        pushLoadPrezzi->setIcon(icon3);

        gridLayout_7->addWidget(pushLoadPrezzi, 1, 3, 1, 1);

        pushInfoTariffe = new QPushButton(groupTariffe);
        pushInfoTariffe->setObjectName(QString::fromUtf8("pushInfoTariffe"));

        gridLayout_7->addWidget(pushInfoTariffe, 1, 4, 1, 1);


        gridLayout_27->addLayout(gridLayout_7, 4, 0, 2, 2);

        label_65 = new QLabel(groupTariffe);
        label_65->setObjectName(QString::fromUtf8("label_65"));
        label_65->setWordWrap(true);

        gridLayout_27->addWidget(label_65, 4, 2, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_27->addItem(horizontalSpacer, 5, 2, 1, 2);


        gridLayout_30->addWidget(groupTariffe, 0, 0, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        gridLayout_29 = new QGridLayout(page_3);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        groupPrezzi = new QGroupBox(page_3);
        groupPrezzi->setObjectName(QString::fromUtf8("groupPrezzi"));
        sizePolicy3.setHeightForWidth(groupPrezzi->sizePolicy().hasHeightForWidth());
        groupPrezzi->setSizePolicy(sizePolicy3);
        groupPrezzi->setFont(font);
        groupPrezzi->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        labelWarn = new QLabel(groupPrezzi);
        labelWarn->setObjectName(QString::fromUtf8("labelWarn"));
        labelWarn->setGeometry(QRect(10, 388, 16, 16));
        sizePolicy3.setHeightForWidth(labelWarn->sizePolicy().hasHeightForWidth());
        labelWarn->setSizePolicy(sizePolicy3);
        gridLayout_9 = new QGridLayout(groupPrezzi);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_51 = new QLabel(groupPrezzi);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_9->addWidget(label_51, 0, 0, 1, 1);

        comboImmBand = new QComboBox(groupPrezzi);
        comboImmBand->setObjectName(QString::fromUtf8("comboImmBand"));

        gridLayout_9->addWidget(comboImmBand, 0, 1, 1, 1);

        label_10 = new QLabel(groupPrezzi);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_9->addWidget(label_10, 0, 2, 1, 1);

        tablePrezziEnergia = new QTableWidget(groupPrezzi);
        if (tablePrezziEnergia->columnCount() < 1)
            tablePrezziEnergia->setColumnCount(1);
        if (tablePrezziEnergia->rowCount() < 12)
            tablePrezziEnergia->setRowCount(12);
        tablePrezziEnergia->setObjectName(QString::fromUtf8("tablePrezziEnergia"));
        tablePrezziEnergia->setRowCount(12);
        tablePrezziEnergia->setColumnCount(1);

        gridLayout_9->addWidget(tablePrezziEnergia, 1, 0, 1, 2);

        tableSummaryBands = new QTableWidget(groupPrezzi);
        if (tableSummaryBands->columnCount() < 2)
            tableSummaryBands->setColumnCount(2);
        if (tableSummaryBands->rowCount() < 12)
            tableSummaryBands->setRowCount(12);
        tableSummaryBands->setObjectName(QString::fromUtf8("tableSummaryBands"));
        tableSummaryBands->setShowGrid(true);
        tableSummaryBands->setGridStyle(Qt::NoPen);
        tableSummaryBands->setRowCount(12);
        tableSummaryBands->setColumnCount(2);

        gridLayout_9->addWidget(tableSummaryBands, 1, 2, 1, 2);

        label_40 = new QLabel(groupPrezzi);
        label_40->setObjectName(QString::fromUtf8("label_40"));

        gridLayout_9->addWidget(label_40, 2, 0, 1, 1);

        dEnergyInflationRate2 = new QDoubleSpinBox(groupPrezzi);
        dEnergyInflationRate2->setObjectName(QString::fromUtf8("dEnergyInflationRate2"));
        sizePolicy5.setHeightForWidth(dEnergyInflationRate2->sizePolicy().hasHeightForWidth());
        dEnergyInflationRate2->setSizePolicy(sizePolicy5);
        dEnergyInflationRate2->setDecimals(4);
        dEnergyInflationRate2->setMaximum(100);

        gridLayout_9->addWidget(dEnergyInflationRate2, 2, 1, 1, 1);

        gridLayout_17 = new QGridLayout();
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        radioSimpleInflation = new QRadioButton(groupPrezzi);
        radioSimpleInflation->setObjectName(QString::fromUtf8("radioSimpleInflation"));
        radioSimpleInflation->setChecked(true);

        gridLayout_17->addWidget(radioSimpleInflation, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        gridLayout_17->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_9->addLayout(gridLayout_17, 2, 2, 1, 1);

        gridLayout_14 = new QGridLayout();
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        label_50 = new QLabel(groupPrezzi);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        gridLayout_14->addWidget(label_50, 0, 0, 1, 2);

        listEnergyPrices = new QListView(groupPrezzi);
        listEnergyPrices->setObjectName(QString::fromUtf8("listEnergyPrices"));
        listEnergyPrices->setMaximumSize(QSize(10000, 300));
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
        listEnergyPrices->setWordWrap(true);

        gridLayout_14->addWidget(listEnergyPrices, 1, 0, 5, 1);

        pushCutPrezziFile = new QPushButton(groupPrezzi);
        pushCutPrezziFile->setObjectName(QString::fromUtf8("pushCutPrezziFile"));

        gridLayout_14->addWidget(pushCutPrezziFile, 1, 1, 1, 1);

        pushSavePrezziEnergiaAs = new QPushButton(groupPrezzi);
        pushSavePrezziEnergiaAs->setObjectName(QString::fromUtf8("pushSavePrezziEnergiaAs"));
        sizePolicy5.setHeightForWidth(pushSavePrezziEnergiaAs->sizePolicy().hasHeightForWidth());
        pushSavePrezziEnergiaAs->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(pushSavePrezziEnergiaAs, 2, 1, 1, 1);

        pushSavePrezziEnergia = new QPushButton(groupPrezzi);
        pushSavePrezziEnergia->setObjectName(QString::fromUtf8("pushSavePrezziEnergia"));
        sizePolicy5.setHeightForWidth(pushSavePrezziEnergia->sizePolicy().hasHeightForWidth());
        pushSavePrezziEnergia->setSizePolicy(sizePolicy5);
        pushSavePrezziEnergia->setIcon(icon2);

        gridLayout_14->addWidget(pushSavePrezziEnergia, 3, 1, 1, 1);

        pushLoadPrezziEnergia = new QPushButton(groupPrezzi);
        pushLoadPrezziEnergia->setObjectName(QString::fromUtf8("pushLoadPrezziEnergia"));
        sizePolicy5.setHeightForWidth(pushLoadPrezziEnergia->sizePolicy().hasHeightForWidth());
        pushLoadPrezziEnergia->setSizePolicy(sizePolicy5);
        pushLoadPrezziEnergia->setIcon(icon3);

        gridLayout_14->addWidget(pushLoadPrezziEnergia, 4, 1, 1, 1);

        pushInfoPrezzi = new QPushButton(groupPrezzi);
        pushInfoPrezzi->setObjectName(QString::fromUtf8("pushInfoPrezzi"));
        sizePolicy5.setHeightForWidth(pushInfoPrezzi->sizePolicy().hasHeightForWidth());
        pushInfoPrezzi->setSizePolicy(sizePolicy5);

        gridLayout_14->addWidget(pushInfoPrezzi, 5, 1, 1, 1);


        gridLayout_9->addLayout(gridLayout_14, 3, 0, 1, 3);

        horizontalSpacer_5 = new QSpacerItem(393, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_9->addItem(horizontalSpacer_5, 3, 3, 1, 1);


        gridLayout_29->addWidget(groupPrezzi, 0, 0, 1, 1);

        stackedWidget->addWidget(page_3);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        gridLayout_37 = new QGridLayout(page_5);
        gridLayout_37->setObjectName(QString::fromUtf8("gridLayout_37"));
        groupMinPrices = new QGroupBox(page_5);
        groupMinPrices->setObjectName(QString::fromUtf8("groupMinPrices"));
        groupMinPrices->setFont(font);
        groupMinPrices->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_36 = new QGridLayout(groupMinPrices);
        gridLayout_36->setObjectName(QString::fromUtf8("gridLayout_36"));
        checkImmIntervals = new QCheckBox(groupMinPrices);
        checkImmIntervals->setObjectName(QString::fromUtf8("checkImmIntervals"));

        gridLayout_36->addWidget(checkImmIntervals, 0, 1, 1, 1);

        qwtMinPrezzi = new QwtPlot(groupMinPrices);
        qwtMinPrezzi->setObjectName(QString::fromUtf8("qwtMinPrezzi"));
        sizePolicy3.setHeightForWidth(qwtMinPrezzi->sizePolicy().hasHeightForWidth());
        qwtMinPrezzi->setSizePolicy(sizePolicy3);

        gridLayout_36->addWidget(qwtMinPrezzi, 0, 3, 4, 1);

        groupImmIntervals = new QGroupBox(groupMinPrices);
        groupImmIntervals->setObjectName(QString::fromUtf8("groupImmIntervals"));
        groupImmIntervals->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_25 = new QGridLayout(groupImmIntervals);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        comboImmissione = new QComboBox(groupImmIntervals);
        comboImmissione->setObjectName(QString::fromUtf8("comboImmissione"));

        gridLayout_25->addWidget(comboImmissione, 1, 0, 1, 2);

        pushImmissione = new QPushButton(groupImmIntervals);
        pushImmissione->setObjectName(QString::fromUtf8("pushImmissione"));
        pushImmissione->setMaximumSize(QSize(30, 16777215));
        pushImmissione->setIcon(icon1);

        gridLayout_25->addWidget(pushImmissione, 1, 2, 1, 1);

        label_33 = new QLabel(groupImmIntervals);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_25->addWidget(label_33, 2, 0, 1, 1);

        dYearlyMinPrice = new QDoubleSpinBox(groupImmIntervals);
        dYearlyMinPrice->setObjectName(QString::fromUtf8("dYearlyMinPrice"));
        dYearlyMinPrice->setDecimals(4);
        dYearlyMinPrice->setMaximum(1e+06);

        gridLayout_25->addWidget(dYearlyMinPrice, 2, 1, 1, 2);


        gridLayout_36->addWidget(groupImmIntervals, 1, 1, 1, 2);

        groupBox_4 = new QGroupBox(groupMinPrices);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_35 = new QGridLayout(groupBox_4);
        gridLayout_35->setObjectName(QString::fromUtf8("gridLayout_35"));
        tableMinPrezziEnergia = new QTableWidget(groupBox_4);
        if (tableMinPrezziEnergia->columnCount() < 1)
            tableMinPrezziEnergia->setColumnCount(1);
        if (tableMinPrezziEnergia->rowCount() < 12)
            tableMinPrezziEnergia->setRowCount(12);
        tableMinPrezziEnergia->setObjectName(QString::fromUtf8("tableMinPrezziEnergia"));
        tableMinPrezziEnergia->setMaximumSize(QSize(16777215, 16777215));
        tableMinPrezziEnergia->setRowCount(12);
        tableMinPrezziEnergia->setColumnCount(1);

        gridLayout_35->addWidget(tableMinPrezziEnergia, 0, 0, 1, 1);


        gridLayout_36->addWidget(groupBox_4, 2, 1, 1, 2);

        gridLayout_18 = new QGridLayout();
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        radioGARCH_2 = new QRadioButton(groupMinPrices);
        radioGARCH_2->setObjectName(QString::fromUtf8("radioGARCH_2"));

        gridLayout_18->addWidget(radioGARCH_2, 0, 0, 1, 2);

        label_41 = new QLabel(groupMinPrices);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout_18->addWidget(label_41, 1, 0, 1, 1);

        dminPricesA1 = new QDoubleSpinBox(groupMinPrices);
        dminPricesA1->setObjectName(QString::fromUtf8("dminPricesA1"));
        dminPricesA1->setDecimals(4);
        dminPricesA1->setValue(0.313);

        gridLayout_18->addWidget(dminPricesA1, 1, 1, 1, 1);

        label_42 = new QLabel(groupMinPrices);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout_18->addWidget(label_42, 2, 0, 1, 1);

        dminPricesB1 = new QDoubleSpinBox(groupMinPrices);
        dminPricesB1->setObjectName(QString::fromUtf8("dminPricesB1"));
        dminPricesB1->setDecimals(4);
        dminPricesB1->setValue(0.318);

        gridLayout_18->addWidget(dminPricesB1, 2, 1, 1, 1);

        label_43 = new QLabel(groupMinPrices);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        gridLayout_18->addWidget(label_43, 3, 0, 1, 1);

        dminPricesO1 = new QDoubleSpinBox(groupMinPrices);
        dminPricesO1->setObjectName(QString::fromUtf8("dminPricesO1"));
        dminPricesO1->setDecimals(4);
        dminPricesO1->setValue(0.062);

        gridLayout_18->addWidget(dminPricesO1, 3, 1, 1, 1);

        label_44 = new QLabel(groupMinPrices);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout_18->addWidget(label_44, 4, 0, 1, 1);

        dminPricesMu = new QDoubleSpinBox(groupMinPrices);
        dminPricesMu->setObjectName(QString::fromUtf8("dminPricesMu"));
        dminPricesMu->setDecimals(4);
        dminPricesMu->setValue(0.049);

        gridLayout_18->addWidget(dminPricesMu, 4, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_18->addItem(verticalSpacer_3, 5, 0, 1, 1);


        gridLayout_36->addLayout(gridLayout_18, 3, 1, 1, 1);

        gridLayout_19 = new QGridLayout();
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        radioSimpleInflation_2 = new QRadioButton(groupMinPrices);
        radioSimpleInflation_2->setObjectName(QString::fromUtf8("radioSimpleInflation_2"));
        radioSimpleInflation_2->setChecked(true);

        gridLayout_19->addWidget(radioSimpleInflation_2, 0, 0, 1, 2);

        label_45 = new QLabel(groupMinPrices);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        gridLayout_19->addWidget(label_45, 1, 0, 1, 1);

        dEnergyInflationRateSell = new QDoubleSpinBox(groupMinPrices);
        dEnergyInflationRateSell->setObjectName(QString::fromUtf8("dEnergyInflationRateSell"));
        dEnergyInflationRateSell->setDecimals(4);
        dEnergyInflationRateSell->setMaximum(100);

        gridLayout_19->addWidget(dEnergyInflationRateSell, 1, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 38, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_19->addItem(verticalSpacer_5, 2, 0, 1, 1);


        gridLayout_36->addLayout(gridLayout_19, 3, 2, 1, 1);

        groupBoxPM = new QGroupBox(groupMinPrices);
        groupBoxPM->setObjectName(QString::fromUtf8("groupBoxPM"));
        groupBoxPM->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_33 = new QGridLayout(groupBoxPM);
        gridLayout_33->setObjectName(QString::fromUtf8("gridLayout_33"));
        gridLayout_20 = new QGridLayout();
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        listMinEnergyPrices = new QListView(groupBoxPM);
        listMinEnergyPrices->setObjectName(QString::fromUtf8("listMinEnergyPrices"));
        sizePolicy1.setHeightForWidth(listMinEnergyPrices->sizePolicy().hasHeightForWidth());
        listMinEnergyPrices->setSizePolicy(sizePolicy1);
        listMinEnergyPrices->setMaximumSize(QSize(10000, 16777215));
        listMinEnergyPrices->setAutoFillBackground(true);
        listMinEnergyPrices->setStyleSheet(QString::fromUtf8(" QListView {\n"
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
        listMinEnergyPrices->setFrameShape(QFrame::Panel);
        listMinEnergyPrices->setFrameShadow(QFrame::Plain);
        listMinEnergyPrices->setWordWrap(true);

        gridLayout_20->addWidget(listMinEnergyPrices, 0, 0, 5, 1);

        pushCutMinPrezziFile = new QPushButton(groupBoxPM);
        pushCutMinPrezziFile->setObjectName(QString::fromUtf8("pushCutMinPrezziFile"));

        gridLayout_20->addWidget(pushCutMinPrezziFile, 0, 1, 1, 1);

        pushSaveMinPrezziEnergiaAs = new QPushButton(groupBoxPM);
        pushSaveMinPrezziEnergiaAs->setObjectName(QString::fromUtf8("pushSaveMinPrezziEnergiaAs"));

        gridLayout_20->addWidget(pushSaveMinPrezziEnergiaAs, 1, 1, 1, 1);

        pushSaveMinPrezziEnergia = new QPushButton(groupBoxPM);
        pushSaveMinPrezziEnergia->setObjectName(QString::fromUtf8("pushSaveMinPrezziEnergia"));
        pushSaveMinPrezziEnergia->setIcon(icon2);

        gridLayout_20->addWidget(pushSaveMinPrezziEnergia, 2, 1, 1, 1);

        pushLoadMinPrezziEnergia = new QPushButton(groupBoxPM);
        pushLoadMinPrezziEnergia->setObjectName(QString::fromUtf8("pushLoadMinPrezziEnergia"));
        pushLoadMinPrezziEnergia->setIcon(icon3);

        gridLayout_20->addWidget(pushLoadMinPrezziEnergia, 3, 1, 1, 1);

        pushInfoPrezziMinimi = new QPushButton(groupBoxPM);
        pushInfoPrezziMinimi->setObjectName(QString::fromUtf8("pushInfoPrezziMinimi"));

        gridLayout_20->addWidget(pushInfoPrezziMinimi, 4, 1, 1, 1);


        gridLayout_33->addLayout(gridLayout_20, 0, 0, 1, 1);


        gridLayout_36->addWidget(groupBoxPM, 4, 0, 2, 3);

        horizontalSpacer_4 = new QSpacerItem(407, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_36->addItem(horizontalSpacer_4, 4, 3, 1, 1);

        labelWarnMin = new QLabel(groupMinPrices);
        labelWarnMin->setObjectName(QString::fromUtf8("labelWarnMin"));

        gridLayout_36->addWidget(labelWarnMin, 5, 1, 1, 1);


        gridLayout_37->addWidget(groupMinPrices, 0, 0, 1, 1);

        stackedWidget->addWidget(page_5);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        gridLayout_38 = new QGridLayout(page_4);
        gridLayout_38->setObjectName(QString::fromUtf8("gridLayout_38"));
        groupBox_3 = new QGroupBox(page_4);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        groupBox_3->setMinimumSize(QSize(0, 80));
        groupBox_3->setMaximumSize(QSize(16777215, 110));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 2px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_10 = new QGridLayout(groupBox_3);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        comboRegime = new QComboBox(groupBox_3);
        comboRegime->setObjectName(QString::fromUtf8("comboRegime"));

        gridLayout_10->addWidget(comboRegime, 0, 0, 1, 1);

        checkCredit = new QCheckBox(groupBox_3);
        checkCredit->setObjectName(QString::fromUtf8("checkCredit"));

        gridLayout_10->addWidget(checkCredit, 0, 1, 1, 2);

        label_58 = new QLabel(groupBox_3);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        gridLayout_10->addWidget(label_58, 1, 0, 1, 1);

        dPotenzakW = new QDoubleSpinBox(groupBox_3);
        dPotenzakW->setObjectName(QString::fromUtf8("dPotenzakW"));
        dPotenzakW->setMaximum(1e+09);

        gridLayout_10->addWidget(dPotenzakW, 1, 1, 1, 1);

        label_59 = new QLabel(groupBox_3);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        gridLayout_10->addWidget(label_59, 1, 2, 1, 1);


        gridLayout_38->addWidget(groupBox_3, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(page_4);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 2px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
" \n"
"      \n"
" }"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_27 = new QLabel(groupBox_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        gridLayout_3->addWidget(label_27, 0, 0, 1, 1);

        dCostoIniziale = new QDoubleSpinBox(groupBox_2);
        dCostoIniziale->setObjectName(QString::fromUtf8("dCostoIniziale"));
        sizePolicy5.setHeightForWidth(dCostoIniziale->sizePolicy().hasHeightForWidth());
        dCostoIniziale->setSizePolicy(sizePolicy5);
        dCostoIniziale->setMaximum(1e+09);

        gridLayout_3->addWidget(dCostoIniziale, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_3->addWidget(label_14, 1, 0, 1, 1);

        dIncentivi = new QDoubleSpinBox(groupBox_2);
        dIncentivi->setObjectName(QString::fromUtf8("dIncentivi"));
        dIncentivi->setDecimals(4);
        dIncentivi->setMaximum(10000);
        dIncentivi->setSingleStep(1);

        gridLayout_3->addWidget(dIncentivi, 1, 1, 1, 1);

        dBonusesYears = new QSpinBox(groupBox_2);
        dBonusesYears->setObjectName(QString::fromUtf8("dBonusesYears"));
        sizePolicy5.setHeightForWidth(dBonusesYears->sizePolicy().hasHeightForWidth());
        dBonusesYears->setSizePolicy(sizePolicy5);
        dBonusesYears->setMaximum(9999999);

        gridLayout_3->addWidget(dBonusesYears, 1, 2, 1, 1);

        label_57 = new QLabel(groupBox_2);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        gridLayout_3->addWidget(label_57, 1, 3, 1, 1);

        label_52 = new QLabel(groupBox_2);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setWordWrap(true);

        gridLayout_3->addWidget(label_52, 2, 0, 1, 1);

        dVAT = new QDoubleSpinBox(groupBox_2);
        dVAT->setObjectName(QString::fromUtf8("dVAT"));
        sizePolicy5.setHeightForWidth(dVAT->sizePolicy().hasHeightForWidth());
        dVAT->setSizePolicy(sizePolicy5);
        dVAT->setDecimals(3);
        dVAT->setMaximum(100);

        gridLayout_3->addWidget(dVAT, 2, 1, 1, 1);

        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_3->addWidget(label_20, 3, 0, 1, 1);

        dIncentiviPerkWp = new QDoubleSpinBox(groupBox_2);
        dIncentiviPerkWp->setObjectName(QString::fromUtf8("dIncentiviPerkWp"));
        dIncentiviPerkWp->setDecimals(4);
        dIncentiviPerkWp->setMaximum(10000);
        dIncentiviPerkWp->setSingleStep(1);

        gridLayout_3->addWidget(dIncentiviPerkWp, 3, 1, 1, 1);

        label_28 = new QLabel(groupBox_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setWordWrap(true);

        gridLayout_3->addWidget(label_28, 4, 0, 1, 1);

        dFinanziamento = new QDoubleSpinBox(groupBox_2);
        dFinanziamento->setObjectName(QString::fromUtf8("dFinanziamento"));
        sizePolicy5.setHeightForWidth(dFinanziamento->sizePolicy().hasHeightForWidth());
        dFinanziamento->setSizePolicy(sizePolicy5);
        dFinanziamento->setDecimals(4);
        dFinanziamento->setMaximum(1e+09);

        gridLayout_3->addWidget(dFinanziamento, 4, 1, 1, 1);

        dFinAnni = new QSpinBox(groupBox_2);
        dFinAnni->setObjectName(QString::fromUtf8("dFinAnni"));
        sizePolicy5.setHeightForWidth(dFinAnni->sizePolicy().hasHeightForWidth());
        dFinAnni->setSizePolicy(sizePolicy5);
        dFinAnni->setMaximum(999999);

        gridLayout_3->addWidget(dFinAnni, 4, 2, 1, 1);

        label_29 = new QLabel(groupBox_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_3->addWidget(label_29, 4, 3, 1, 1);

        label_84 = new QLabel(groupBox_2);
        label_84->setObjectName(QString::fromUtf8("label_84"));
        label_84->setMinimumSize(QSize(0, 28));
        label_84->setWordWrap(true);

        gridLayout_3->addWidget(label_84, 4, 4, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 5, 0, 1, 1);

        dTassoInflazione = new QDoubleSpinBox(groupBox_2);
        dTassoInflazione->setObjectName(QString::fromUtf8("dTassoInflazione"));
        sizePolicy5.setHeightForWidth(dTassoInflazione->sizePolicy().hasHeightForWidth());
        dTassoInflazione->setSizePolicy(sizePolicy5);
        dTassoInflazione->setDecimals(4);
        dTassoInflazione->setMaximum(100);

        gridLayout_3->addWidget(dTassoInflazione, 5, 1, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMinimumSize(QSize(0, 28));
        label_16->setWordWrap(false);

        gridLayout_3->addWidget(label_16, 6, 0, 1, 1);

        dLoanInterestRate = new QDoubleSpinBox(groupBox_2);
        dLoanInterestRate->setObjectName(QString::fromUtf8("dLoanInterestRate"));
        dLoanInterestRate->setDecimals(4);
        dLoanInterestRate->setMaximum(100);

        gridLayout_3->addWidget(dLoanInterestRate, 6, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        gridLayout_3->addWidget(label_2, 7, 0, 1, 1);

        dDiscountRate = new QDoubleSpinBox(groupBox_2);
        dDiscountRate->setObjectName(QString::fromUtf8("dDiscountRate"));
        sizePolicy5.setHeightForWidth(dDiscountRate->sizePolicy().hasHeightForWidth());
        dDiscountRate->setSizePolicy(sizePolicy5);
        dDiscountRate->setDecimals(4);
        dDiscountRate->setMaximum(100);

        gridLayout_3->addWidget(dDiscountRate, 7, 1, 1, 1);

        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_3->addWidget(label_18, 8, 0, 1, 1);

        dPeriodo = new QSpinBox(groupBox_2);
        dPeriodo->setObjectName(QString::fromUtf8("dPeriodo"));
        sizePolicy5.setHeightForWidth(dPeriodo->sizePolicy().hasHeightForWidth());
        dPeriodo->setSizePolicy(sizePolicy5);

        gridLayout_3->addWidget(dPeriodo, 8, 1, 1, 1);


        gridLayout_38->addWidget(groupBox_2, 1, 0, 1, 2);

        groupBox = new QGroupBox(page_4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8(" \n"
"QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 2px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_12 = new QGridLayout(groupBox);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setWordWrap(true);

        gridLayout_12->addWidget(label_11, 0, 0, 1, 1);

        dManutenzioneAnno = new QDoubleSpinBox(groupBox);
        dManutenzioneAnno->setObjectName(QString::fromUtf8("dManutenzioneAnno"));
        sizePolicy5.setHeightForWidth(dManutenzioneAnno->sizePolicy().hasHeightForWidth());
        dManutenzioneAnno->setSizePolicy(sizePolicy5);
        dManutenzioneAnno->setMaximum(1e+09);

        gridLayout_12->addWidget(dManutenzioneAnno, 0, 1, 1, 4);

        label_47 = new QLabel(groupBox);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setWordWrap(true);

        gridLayout_12->addWidget(label_47, 1, 0, 1, 1);

        dManutenzioneS = new QDoubleSpinBox(groupBox);
        dManutenzioneS->setObjectName(QString::fromUtf8("dManutenzioneS"));
        sizePolicy5.setHeightForWidth(dManutenzioneS->sizePolicy().hasHeightForWidth());
        dManutenzioneS->setSizePolicy(sizePolicy5);
        dManutenzioneS->setMaximum(1e+09);

        gridLayout_12->addWidget(dManutenzioneS, 1, 1, 1, 4);

        label_48 = new QLabel(groupBox);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_12->addWidget(label_48, 2, 0, 1, 1);

        dManutenzioneSFreq = new QSpinBox(groupBox);
        dManutenzioneSFreq->setObjectName(QString::fromUtf8("dManutenzioneSFreq"));
        sizePolicy5.setHeightForWidth(dManutenzioneSFreq->sizePolicy().hasHeightForWidth());
        dManutenzioneSFreq->setSizePolicy(sizePolicy5);

        gridLayout_12->addWidget(dManutenzioneSFreq, 2, 1, 1, 4);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_12->addWidget(label_13, 3, 0, 1, 1);

        dAffitti = new QDoubleSpinBox(groupBox);
        dAffitti->setObjectName(QString::fromUtf8("dAffitti"));
        sizePolicy5.setHeightForWidth(dAffitti->sizePolicy().hasHeightForWidth());
        dAffitti->setSizePolicy(sizePolicy5);
        dAffitti->setMaximum(1e+09);

        gridLayout_12->addWidget(dAffitti, 3, 1, 1, 4);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_12->addWidget(label_17, 4, 0, 1, 1);

        dAltro = new QDoubleSpinBox(groupBox);
        dAltro->setObjectName(QString::fromUtf8("dAltro"));
        sizePolicy5.setHeightForWidth(dAltro->sizePolicy().hasHeightForWidth());
        dAltro->setSizePolicy(sizePolicy5);
        dAltro->setMaximum(1e+09);

        gridLayout_12->addWidget(dAltro, 4, 1, 1, 4);

        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setWordWrap(true);

        gridLayout_12->addWidget(label_19, 5, 0, 1, 1);

        dAssicurazione = new QDoubleSpinBox(groupBox);
        dAssicurazione->setObjectName(QString::fromUtf8("dAssicurazione"));
        sizePolicy5.setHeightForWidth(dAssicurazione->sizePolicy().hasHeightForWidth());
        dAssicurazione->setSizePolicy(sizePolicy5);
        dAssicurazione->setMaximum(1e+09);

        gridLayout_12->addWidget(dAssicurazione, 5, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(94, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_3, 5, 2, 1, 1);

        label_55 = new QLabel(groupBox);
        label_55->setObjectName(QString::fromUtf8("label_55"));

        gridLayout_12->addWidget(label_55, 5, 3, 1, 1);

        dAssicurazioneAnni = new QSpinBox(groupBox);
        dAssicurazioneAnni->setObjectName(QString::fromUtf8("dAssicurazioneAnni"));
        sizePolicy5.setHeightForWidth(dAssicurazioneAnni->sizePolicy().hasHeightForWidth());
        dAssicurazioneAnni->setSizePolicy(sizePolicy5);
        dAssicurazioneAnni->setMaximum(999999999);

        gridLayout_12->addWidget(dAssicurazioneAnni, 5, 4, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_12->addItem(verticalSpacer_6, 6, 1, 1, 1);


        gridLayout_38->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_9 = new QGroupBox(page_4);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        sizePolicy3.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy3);
        groupBox_9->setFont(font);
        groupBox_9->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_2 = new QGridLayout(groupBox_9);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_24 = new QLabel(groupBox_9);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_2->addWidget(label_24, 0, 0, 1, 1);

        dTaxReductionInterest = new QDoubleSpinBox(groupBox_9);
        dTaxReductionInterest->setObjectName(QString::fromUtf8("dTaxReductionInterest"));
        sizePolicy5.setHeightForWidth(dTaxReductionInterest->sizePolicy().hasHeightForWidth());
        dTaxReductionInterest->setSizePolicy(sizePolicy5);
        dTaxReductionInterest->setDecimals(3);
        dTaxReductionInterest->setMaximum(100);

        gridLayout_2->addWidget(dTaxReductionInterest, 0, 1, 1, 1);

        label = new QLabel(groupBox_9);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        dTaxReduction = new QDoubleSpinBox(groupBox_9);
        dTaxReduction->setObjectName(QString::fromUtf8("dTaxReduction"));
        sizePolicy5.setHeightForWidth(dTaxReduction->sizePolicy().hasHeightForWidth());
        dTaxReduction->setSizePolicy(sizePolicy5);
        dTaxReduction->setDecimals(3);
        dTaxReduction->setMaximum(100);

        gridLayout_2->addWidget(dTaxReduction, 1, 1, 1, 1);

        dTaxReductionVAT = new QDoubleSpinBox(groupBox_9);
        dTaxReductionVAT->setObjectName(QString::fromUtf8("dTaxReductionVAT"));
        sizePolicy5.setHeightForWidth(dTaxReductionVAT->sizePolicy().hasHeightForWidth());
        dTaxReductionVAT->setSizePolicy(sizePolicy5);
        dTaxReductionVAT->setDecimals(3);
        dTaxReductionVAT->setMaximum(100);

        gridLayout_2->addWidget(dTaxReductionVAT, 3, 1, 1, 1);

        label_53 = new QLabel(groupBox_9);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setWordWrap(true);

        gridLayout_2->addWidget(label_53, 5, 0, 1, 1);

        dAmmortamento = new QDoubleSpinBox(groupBox_9);
        dAmmortamento->setObjectName(QString::fromUtf8("dAmmortamento"));
        sizePolicy5.setHeightForWidth(dAmmortamento->sizePolicy().hasHeightForWidth());
        dAmmortamento->setSizePolicy(sizePolicy5);
        dAmmortamento->setDecimals(3);
        dAmmortamento->setMaximum(100);
        dAmmortamento->setValue(9);

        gridLayout_2->addWidget(dAmmortamento, 5, 1, 1, 1);

        label_49 = new QLabel(groupBox_9);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        gridLayout_2->addWidget(label_49, 3, 0, 1, 1);

        dReductionInitialCost = new QDoubleSpinBox(groupBox_9);
        dReductionInitialCost->setObjectName(QString::fromUtf8("dReductionInitialCost"));
        dReductionInitialCost->setMaximum(100);

        gridLayout_2->addWidget(dReductionInitialCost, 2, 1, 1, 1);

        label_83 = new QLabel(groupBox_9);
        label_83->setObjectName(QString::fromUtf8("label_83"));

        gridLayout_2->addWidget(label_83, 2, 0, 1, 1);


        gridLayout_38->addWidget(groupBox_9, 2, 1, 1, 1);

        stackedWidget->addWidget(page_4);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        gridLayout_31 = new QGridLayout(page_7);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        groupTax = new QGroupBox(page_7);
        groupTax->setObjectName(QString::fromUtf8("groupTax"));
        sizePolicy4.setHeightForWidth(groupTax->sizePolicy().hasHeightForWidth());
        groupTax->setSizePolicy(sizePolicy4);
        groupTax->setFont(font);
        groupTax->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                       stop: 0 #E0E0E0, stop: 1 #FFFFFF);\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 4ex; /* leave space at the top for the title */\n"
" }\n"
"QGroupBox::title {\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
"      \n"
" }"));
        gridLayout_11 = new QGridLayout(groupTax);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_24 = new QGridLayout();
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        label_67 = new QLabel(groupTax);
        label_67->setObjectName(QString::fromUtf8("label_67"));
        label_67->setWordWrap(true);

        gridLayout_24->addWidget(label_67, 0, 1, 1, 1);

        label_68 = new QLabel(groupTax);
        label_68->setObjectName(QString::fromUtf8("label_68"));
        label_68->setWordWrap(true);

        gridLayout_24->addWidget(label_68, 0, 2, 1, 1);

        label_69 = new QLabel(groupTax);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setWordWrap(true);

        gridLayout_24->addWidget(label_69, 0, 3, 1, 1);

        label_70 = new QLabel(groupTax);
        label_70->setObjectName(QString::fromUtf8("label_70"));
        label_70->setWordWrap(true);

        gridLayout_24->addWidget(label_70, 1, 0, 1, 1);

        dTIvaBonus = new QDoubleSpinBox(groupTax);
        dTIvaBonus->setObjectName(QString::fromUtf8("dTIvaBonus"));
        sizePolicy5.setHeightForWidth(dTIvaBonus->sizePolicy().hasHeightForWidth());
        dTIvaBonus->setSizePolicy(sizePolicy5);
        dTIvaBonus->setMaximum(100);

        gridLayout_24->addWidget(dTIvaBonus, 1, 1, 1, 1);

        dTIvaCS = new QDoubleSpinBox(groupTax);
        dTIvaCS->setObjectName(QString::fromUtf8("dTIvaCS"));
        sizePolicy5.setHeightForWidth(dTIvaCS->sizePolicy().hasHeightForWidth());
        dTIvaCS->setSizePolicy(sizePolicy5);
        dTIvaCS->setMaximum(100);

        gridLayout_24->addWidget(dTIvaCS, 1, 2, 1, 1);

        dTIvaEn = new QDoubleSpinBox(groupTax);
        dTIvaEn->setObjectName(QString::fromUtf8("dTIvaEn"));
        sizePolicy5.setHeightForWidth(dTIvaEn->sizePolicy().hasHeightForWidth());
        dTIvaEn->setSizePolicy(sizePolicy5);
        dTIvaEn->setMaximum(100);

        gridLayout_24->addWidget(dTIvaEn, 1, 3, 1, 1);

        label_71 = new QLabel(groupTax);
        label_71->setObjectName(QString::fromUtf8("label_71"));
        label_71->setWordWrap(true);

        gridLayout_24->addWidget(label_71, 2, 0, 1, 1);

        dTIrpefBonus = new QDoubleSpinBox(groupTax);
        dTIrpefBonus->setObjectName(QString::fromUtf8("dTIrpefBonus"));
        sizePolicy5.setHeightForWidth(dTIrpefBonus->sizePolicy().hasHeightForWidth());
        dTIrpefBonus->setSizePolicy(sizePolicy5);
        dTIrpefBonus->setMaximum(100);

        gridLayout_24->addWidget(dTIrpefBonus, 2, 1, 1, 1);

        dTIrpefCS = new QDoubleSpinBox(groupTax);
        dTIrpefCS->setObjectName(QString::fromUtf8("dTIrpefCS"));
        sizePolicy5.setHeightForWidth(dTIrpefCS->sizePolicy().hasHeightForWidth());
        dTIrpefCS->setSizePolicy(sizePolicy5);
        dTIrpefCS->setMaximum(100);

        gridLayout_24->addWidget(dTIrpefCS, 2, 2, 1, 1);

        dTIrpefEn = new QDoubleSpinBox(groupTax);
        dTIrpefEn->setObjectName(QString::fromUtf8("dTIrpefEn"));
        sizePolicy5.setHeightForWidth(dTIrpefEn->sizePolicy().hasHeightForWidth());
        dTIrpefEn->setSizePolicy(sizePolicy5);
        dTIrpefEn->setMaximum(100);

        gridLayout_24->addWidget(dTIrpefEn, 2, 3, 1, 1);

        label_72 = new QLabel(groupTax);
        label_72->setObjectName(QString::fromUtf8("label_72"));
        label_72->setWordWrap(true);

        gridLayout_24->addWidget(label_72, 3, 0, 1, 1);

        dTIrapBonus = new QDoubleSpinBox(groupTax);
        dTIrapBonus->setObjectName(QString::fromUtf8("dTIrapBonus"));
        sizePolicy5.setHeightForWidth(dTIrapBonus->sizePolicy().hasHeightForWidth());
        dTIrapBonus->setSizePolicy(sizePolicy5);
        dTIrapBonus->setMaximum(100);

        gridLayout_24->addWidget(dTIrapBonus, 3, 1, 1, 1);

        dTIrapCS = new QDoubleSpinBox(groupTax);
        dTIrapCS->setObjectName(QString::fromUtf8("dTIrapCS"));
        sizePolicy5.setHeightForWidth(dTIrapCS->sizePolicy().hasHeightForWidth());
        dTIrapCS->setSizePolicy(sizePolicy5);
        dTIrapCS->setMaximum(100);

        gridLayout_24->addWidget(dTIrapCS, 3, 2, 1, 1);

        dTIrapEn = new QDoubleSpinBox(groupTax);
        dTIrapEn->setObjectName(QString::fromUtf8("dTIrapEn"));
        sizePolicy5.setHeightForWidth(dTIrapEn->sizePolicy().hasHeightForWidth());
        dTIrapEn->setSizePolicy(sizePolicy5);
        dTIrapEn->setMaximum(100);

        gridLayout_24->addWidget(dTIrapEn, 3, 3, 1, 1);

        label_73 = new QLabel(groupTax);
        label_73->setObjectName(QString::fromUtf8("label_73"));
        label_73->setWordWrap(true);

        gridLayout_24->addWidget(label_73, 4, 0, 1, 1);

        dTIresBonus = new QDoubleSpinBox(groupTax);
        dTIresBonus->setObjectName(QString::fromUtf8("dTIresBonus"));
        sizePolicy5.setHeightForWidth(dTIresBonus->sizePolicy().hasHeightForWidth());
        dTIresBonus->setSizePolicy(sizePolicy5);
        dTIresBonus->setMaximum(100);

        gridLayout_24->addWidget(dTIresBonus, 4, 1, 1, 1);

        dTIresCS = new QDoubleSpinBox(groupTax);
        dTIresCS->setObjectName(QString::fromUtf8("dTIresCS"));
        sizePolicy5.setHeightForWidth(dTIresCS->sizePolicy().hasHeightForWidth());
        dTIresCS->setSizePolicy(sizePolicy5);
        dTIresCS->setMaximum(100);

        gridLayout_24->addWidget(dTIresCS, 4, 2, 1, 1);

        dTIresEn = new QDoubleSpinBox(groupTax);
        dTIresEn->setObjectName(QString::fromUtf8("dTIresEn"));
        sizePolicy5.setHeightForWidth(dTIresEn->sizePolicy().hasHeightForWidth());
        dTIresEn->setSizePolicy(sizePolicy5);
        dTIresEn->setMaximum(100);

        gridLayout_24->addWidget(dTIresEn, 4, 3, 1, 1);

        dTAltroEn = new QDoubleSpinBox(groupTax);
        dTAltroEn->setObjectName(QString::fromUtf8("dTAltroEn"));
        dTAltroEn->setMaximum(100);

        gridLayout_24->addWidget(dTAltroEn, 5, 3, 1, 1);

        dTAltroCS = new QDoubleSpinBox(groupTax);
        dTAltroCS->setObjectName(QString::fromUtf8("dTAltroCS"));
        dTAltroCS->setMaximum(100);

        gridLayout_24->addWidget(dTAltroCS, 5, 2, 1, 1);

        dTAltroBonus = new QDoubleSpinBox(groupTax);
        dTAltroBonus->setObjectName(QString::fromUtf8("dTAltroBonus"));

        gridLayout_24->addWidget(dTAltroBonus, 5, 1, 1, 1);

        label_75 = new QLabel(groupTax);
        label_75->setObjectName(QString::fromUtf8("label_75"));

        gridLayout_24->addWidget(label_75, 5, 0, 1, 1);


        gridLayout_11->addLayout(gridLayout_24, 0, 0, 1, 5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_74 = new QLabel(groupTax);
        label_74->setObjectName(QString::fromUtf8("label_74"));

        verticalLayout->addWidget(label_74);

        listTaxes = new QListView(groupTax);
        listTaxes->setObjectName(QString::fromUtf8("listTaxes"));
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(listTaxes->sizePolicy().hasHeightForWidth());
        listTaxes->setSizePolicy(sizePolicy7);

        verticalLayout->addWidget(listTaxes);


        gridLayout_11->addLayout(verticalLayout, 1, 0, 1, 5);

        horizontalSpacer_2 = new QSpacerItem(350, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_2, 1, 5, 1, 1);

        pushCutTaxFile = new QPushButton(groupTax);
        pushCutTaxFile->setObjectName(QString::fromUtf8("pushCutTaxFile"));
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(pushCutTaxFile->sizePolicy().hasHeightForWidth());
        pushCutTaxFile->setSizePolicy(sizePolicy8);

        gridLayout_11->addWidget(pushCutTaxFile, 2, 0, 1, 1);

        pushSaveTax = new QPushButton(groupTax);
        pushSaveTax->setObjectName(QString::fromUtf8("pushSaveTax"));
        sizePolicy8.setHeightForWidth(pushSaveTax->sizePolicy().hasHeightForWidth());
        pushSaveTax->setSizePolicy(sizePolicy8);
        pushSaveTax->setIcon(icon2);

        gridLayout_11->addWidget(pushSaveTax, 2, 1, 1, 1);

        pushSaveTaxAs = new QPushButton(groupTax);
        pushSaveTaxAs->setObjectName(QString::fromUtf8("pushSaveTaxAs"));
        sizePolicy8.setHeightForWidth(pushSaveTaxAs->sizePolicy().hasHeightForWidth());
        pushSaveTaxAs->setSizePolicy(sizePolicy8);

        gridLayout_11->addWidget(pushSaveTaxAs, 2, 2, 1, 1);

        pushLoadTax = new QPushButton(groupTax);
        pushLoadTax->setObjectName(QString::fromUtf8("pushLoadTax"));
        sizePolicy8.setHeightForWidth(pushLoadTax->sizePolicy().hasHeightForWidth());
        pushLoadTax->setSizePolicy(sizePolicy8);
        pushLoadTax->setIcon(icon3);

        gridLayout_11->addWidget(pushLoadTax, 2, 3, 1, 1);

        pushInfoTax = new QPushButton(groupTax);
        pushInfoTax->setObjectName(QString::fromUtf8("pushInfoTax"));
        sizePolicy8.setHeightForWidth(pushInfoTax->sizePolicy().hasHeightForWidth());
        pushInfoTax->setSizePolicy(sizePolicy8);

        gridLayout_11->addWidget(pushInfoTax, 2, 4, 1, 1);


        gridLayout_31->addWidget(groupTax, 0, 0, 1, 1);

        verticalSpacer_10 = new QSpacerItem(20, 460, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_31->addItem(verticalSpacer_10, 1, 0, 1, 1);

        stackedWidget->addWidget(page_7);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        stackedWidget->addWidget(page_6);

        gridLayout_23->addWidget(stackedWidget, 0, 1, 1, 1);

        QWidget::setTabOrder(dLoss, comboTariffeIntervals);
        QWidget::setTabOrder(comboTariffeIntervals, pushTariffeIntervals);
        QWidget::setTabOrder(pushTariffeIntervals, dTrasmissionekWh);
        QWidget::setTabOrder(dTrasmissionekWh, dTrasmissionekW);
        QWidget::setTabOrder(dTrasmissionekW, dTrasmissioneAnno);
        QWidget::setTabOrder(dTrasmissioneAnno, dDistribuzionekWh);
        QWidget::setTabOrder(dDistribuzionekWh, dDistribuzionekW);
        QWidget::setTabOrder(dDistribuzionekW, dDistribuzioneAnno);
        QWidget::setTabOrder(dDistribuzioneAnno, dMisurakWh);
        QWidget::setTabOrder(dMisurakWh, dMisurakW);
        QWidget::setTabOrder(dMisurakW, dMisuraAnno);
        QWidget::setTabOrder(dMisuraAnno, dDISPkWh);
        QWidget::setTabOrder(dDISPkWh, dDISPkW);
        QWidget::setTabOrder(dDISPkW, dDISP);
        QWidget::setTabOrder(dDISP, dAUCkWh);
        QWidget::setTabOrder(dAUCkWh, dAUCkW);
        QWidget::setTabOrder(dAUCkW, dAUCanno);
        QWidget::setTabOrder(dAUCanno, dMCTkWh);
        QWidget::setTabOrder(dMCTkWh, dPerditaTrasmissione);
        QWidget::setTabOrder(dPerditaTrasmissione, dCostiAmm);
        QWidget::setTabOrder(dCostiAmm, dLimitCostiAmm);
        QWidget::setTabOrder(dLimitCostiAmm, dCTRkWh);
        QWidget::setTabOrder(dCTRkWh, dFattCTR);
        QWidget::setTabOrder(dFattCTR, dAltriCostiMensili);
        QWidget::setTabOrder(dAltriCostiMensili, listTariffe);
        QWidget::setTabOrder(listTariffe, pushCutOneriFile);
        QWidget::setTabOrder(pushCutOneriFile, pushSavePrezziAs);
        QWidget::setTabOrder(pushSavePrezziAs, pushSavePrezzi);
        QWidget::setTabOrder(pushSavePrezzi, pushLoadPrezzi);
        QWidget::setTabOrder(pushLoadPrezzi, pushInfoTariffe);
        QWidget::setTabOrder(pushInfoTariffe, dBandsInflationRate);
        QWidget::setTabOrder(dBandsInflationRate, pushCutBandFile);
        QWidget::setTabOrder(pushCutBandFile, pushSaveBandsAs);
        QWidget::setTabOrder(pushSaveBandsAs, pushSaveBands);
        QWidget::setTabOrder(pushSaveBands, pushLoadBands);
        QWidget::setTabOrder(pushLoadBands, pushInfoBands);
        QWidget::setTabOrder(pushInfoBands, listBands);
        QWidget::setTabOrder(listBands, treeWidget);
        QWidget::setTabOrder(treeWidget, pushUndo);
        QWidget::setTabOrder(pushUndo, comboIntervals);
        QWidget::setTabOrder(comboIntervals, dValue);
        QWidget::setTabOrder(dValue, pushClearAllBands);
        QWidget::setTabOrder(pushClearAllBands, spinDa);
        QWidget::setTabOrder(spinDa, pushAddConsumo);
        QWidget::setTabOrder(pushAddConsumo, comboBands);
        QWidget::setTabOrder(comboBands, spinA);
        QWidget::setTabOrder(spinA, tableBandsView);
        QWidget::setTabOrder(tableBandsView, dVATonEn);
        QWidget::setTabOrder(dVATonEn, dIMPkWh);
        QWidget::setTabOrder(dIMPkWh, tablePrezziEnergia);
        QWidget::setTabOrder(tablePrezziEnergia, radioSimpleInflation);
        QWidget::setTabOrder(radioSimpleInflation, listEnergyPrices);
        QWidget::setTabOrder(listEnergyPrices, pushCutPrezziFile);
        QWidget::setTabOrder(pushCutPrezziFile, pushSavePrezziEnergiaAs);
        QWidget::setTabOrder(pushSavePrezziEnergiaAs, pushSavePrezziEnergia);
        QWidget::setTabOrder(pushSavePrezziEnergia, pushLoadPrezziEnergia);
        QWidget::setTabOrder(pushLoadPrezziEnergia, pushInfoPrezzi);
        QWidget::setTabOrder(pushInfoPrezzi, checkImmIntervals);
        QWidget::setTabOrder(checkImmIntervals, comboImmissione);
        QWidget::setTabOrder(comboImmissione, pushImmissione);
        QWidget::setTabOrder(pushImmissione, dYearlyMinPrice);
        QWidget::setTabOrder(dYearlyMinPrice, tableMinPrezziEnergia);
        QWidget::setTabOrder(tableMinPrezziEnergia, radioGARCH_2);
        QWidget::setTabOrder(radioGARCH_2, dminPricesA1);
        QWidget::setTabOrder(dminPricesA1, dminPricesB1);
        QWidget::setTabOrder(dminPricesB1, dminPricesO1);
        QWidget::setTabOrder(dminPricesO1, dminPricesMu);
        QWidget::setTabOrder(dminPricesMu, radioSimpleInflation_2);
        QWidget::setTabOrder(radioSimpleInflation_2, dEnergyInflationRateSell);
        QWidget::setTabOrder(dEnergyInflationRateSell, listMinEnergyPrices);
        QWidget::setTabOrder(listMinEnergyPrices, pushCutMinPrezziFile);
        QWidget::setTabOrder(pushCutMinPrezziFile, pushSaveMinPrezziEnergiaAs);
        QWidget::setTabOrder(pushSaveMinPrezziEnergiaAs, pushSaveMinPrezziEnergia);
        QWidget::setTabOrder(pushSaveMinPrezziEnergia, pushLoadMinPrezziEnergia);
        QWidget::setTabOrder(pushLoadMinPrezziEnergia, pushInfoPrezziMinimi);
        QWidget::setTabOrder(pushInfoPrezziMinimi, comboRegime);
        QWidget::setTabOrder(comboRegime, checkCredit);
        QWidget::setTabOrder(checkCredit, dPotenzakW);
        QWidget::setTabOrder(dPotenzakW, dCostoIniziale);
        QWidget::setTabOrder(dCostoIniziale, dIncentivi);
        QWidget::setTabOrder(dIncentivi, dBonusesYears);
        QWidget::setTabOrder(dBonusesYears, dVAT);
        QWidget::setTabOrder(dVAT, dIncentiviPerkWp);
        QWidget::setTabOrder(dIncentiviPerkWp, dFinanziamento);
        QWidget::setTabOrder(dFinanziamento, dFinAnni);
        QWidget::setTabOrder(dFinAnni, dTassoInflazione);
        QWidget::setTabOrder(dTassoInflazione, dLoanInterestRate);
        QWidget::setTabOrder(dLoanInterestRate, dDiscountRate);
        QWidget::setTabOrder(dDiscountRate, dPeriodo);
        QWidget::setTabOrder(dPeriodo, dManutenzioneAnno);
        QWidget::setTabOrder(dManutenzioneAnno, dManutenzioneS);
        QWidget::setTabOrder(dManutenzioneS, dManutenzioneSFreq);
        QWidget::setTabOrder(dManutenzioneSFreq, dAffitti);
        QWidget::setTabOrder(dAffitti, dAltro);
        QWidget::setTabOrder(dAltro, dAssicurazione);
        QWidget::setTabOrder(dAssicurazione, dAssicurazioneAnni);
        QWidget::setTabOrder(dAssicurazioneAnni, dTaxReductionInterest);
        QWidget::setTabOrder(dTaxReductionInterest, dTaxReduction);
        QWidget::setTabOrder(dTaxReduction, dTaxReductionVAT);
        QWidget::setTabOrder(dTaxReductionVAT, dAmmortamento);
        QWidget::setTabOrder(dAmmortamento, dReductionInitialCost);
        QWidget::setTabOrder(dReductionInitialCost, dTIvaBonus);
        QWidget::setTabOrder(dTIvaBonus, dTIvaCS);
        QWidget::setTabOrder(dTIvaCS, dTIvaEn);
        QWidget::setTabOrder(dTIvaEn, dTIrpefBonus);
        QWidget::setTabOrder(dTIrpefBonus, dTIrpefCS);
        QWidget::setTabOrder(dTIrpefCS, dTIrpefEn);
        QWidget::setTabOrder(dTIrpefEn, dTIrapBonus);
        QWidget::setTabOrder(dTIrapBonus, dTIrapCS);
        QWidget::setTabOrder(dTIrapCS, dTIrapEn);
        QWidget::setTabOrder(dTIrapEn, dTIresBonus);
        QWidget::setTabOrder(dTIresBonus, dTIresCS);
        QWidget::setTabOrder(dTIresCS, dTIresEn);
        QWidget::setTabOrder(dTIresEn, dTAltroEn);
        QWidget::setTabOrder(dTAltroEn, dTAltroCS);
        QWidget::setTabOrder(dTAltroCS, dTAltroBonus);
        QWidget::setTabOrder(dTAltroBonus, listTaxes);
        QWidget::setTabOrder(listTaxes, pushCutTaxFile);
        QWidget::setTabOrder(pushCutTaxFile, pushSaveTax);
        QWidget::setTabOrder(pushSaveTax, pushSaveTaxAs);
        QWidget::setTabOrder(pushSaveTaxAs, pushLoadTax);
        QWidget::setTabOrder(pushLoadTax, pushInfoTax);

        retranslateUi(widgetEcoVal);

        stackedWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(widgetEcoVal);
    } // setupUi

    void retranslateUi(QWidget *widgetEcoVal)
    {
        widgetEcoVal->setWindowTitle(QApplication::translate("widgetEcoVal", "Parametri economici", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("widgetEcoVal", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("widgetEcoVal", "Costi energia per fasce orarie", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("widgetEcoVal", "Oneri accessori e disp.", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem3->setText(0, QApplication::translate("widgetEcoVal", "Prezzi Energia immessa", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem4->setText(0, QApplication::translate("widgetEcoVal", "Prezzi Minimi garantiti", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem5->setText(0, QApplication::translate("widgetEcoVal", "Regime e Investimento", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = treeWidget->topLevelItem(5);
        ___qtreewidgetitem6->setText(0, QApplication::translate("widgetEcoVal", "Imposte", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        groupBands->setTitle(QApplication::translate("widgetEcoVal", "Valori orari", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("widgetEcoVal", "Denominazione", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("widgetEcoVal", "Dalle ore", 0, QApplication::UnicodeUTF8));
        pushClearAllBands->setText(QApplication::translate("widgetEcoVal", "Cancella tutto", 0, QApplication::UnicodeUTF8));
        pushUndo->setText(QApplication::translate("widgetEcoVal", "Annulla cancellazione", 0, QApplication::UnicodeUTF8));
        label_76->setText(QApplication::translate("widgetEcoVal", "Intervallo di consumo", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("widgetEcoVal", "c/kWh", 0, QApplication::UnicodeUTF8));
        pushAddConsumo->setText(QString());
        comboBands->clear();
        comboBands->insertItems(0, QStringList()
         << QApplication::translate("widgetEcoVal", "B1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B1 (sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B2 (sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B3 (sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B1 (domenica)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B2 (domenica)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B3 (domenica)", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QApplication::translate("widgetEcoVal", "Alle ore", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox_10->setToolTip(QApplication::translate("widgetEcoVal", "<p> Imposte pagate in bolletta, come IVA, Erario, Accisa</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_10->setTitle(QApplication::translate("widgetEcoVal", "Imposte fisse", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_81->setToolTip(QApplication::translate("widgetEcoVal", "<p> IVA pagata in bolletta</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_81->setText(QApplication::translate("widgetEcoVal", "IVA su imponibile (%)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dVATonEn->setToolTip(QApplication::translate("widgetEcoVal", "<p> IVA pagata in bolletta</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_82->setToolTip(QApplication::translate("widgetEcoVal", "<p> Imposte pagate in bolletta, Erario, Accisa</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_82->setText(QApplication::translate("widgetEcoVal", "Altro (%)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dIMPkWh->setToolTip(QApplication::translate("widgetEcoVal", "<p> Imposte pagate in bolletta, Erario, Accisa</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_66->setText(QApplication::translate("widgetEcoVal", "Tasso inflazione costo energia", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("widgetEcoVal", "File recenti", 0, QApplication::UnicodeUTF8));
        pushCutBandFile->setText(QApplication::translate("widgetEcoVal", "Elimina", 0, QApplication::UnicodeUTF8));
        pushSaveBandsAs->setText(QApplication::translate("widgetEcoVal", "Salva come", 0, QApplication::UnicodeUTF8));
        pushSaveBands->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
        pushLoadBands->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
        pushInfoBands->setText(QApplication::translate("widgetEcoVal", "Info", 0, QApplication::UnicodeUTF8));
        label_4->setText(QString());
        label_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        groupTariffe->setToolTip(QApplication::translate("widgetEcoVal", "<p>I valori monetari  sono intesi nell'unit&agrave; monetaria corrente. Ad essi viene applicata l'IVA su imponibile</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupTariffe->setTitle(QApplication::translate("widgetEcoVal", "Oneri accessori e dispacciamento", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("widgetEcoVal", "Fattore perdite Energia Immessa", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dLoss->setToolTip(QApplication::translate("widgetEcoVal", "<p>Coefficiente di maggiorazione dell'energia immessa</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_77->setText(QApplication::translate("widgetEcoVal", "Intervalli di consumo", 0, QApplication::UnicodeUTF8));
        pushTariffeIntervals->setText(QString());
#ifndef QT_NO_TOOLTIP
        groupTras->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupTras->setTitle(QApplication::translate("widgetEcoVal", "Tariffe Trasmissione", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("widgetEcoVal", " (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("widgetEcoVal", " (c/kW)", 0, QApplication::UnicodeUTF8));
        label_54->setText(QApplication::translate("widgetEcoVal", " (c/anno)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupDist->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupDist->setTitle(QApplication::translate("widgetEcoVal", "Tariffe Distribuzione", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("widgetEcoVal", " (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("widgetEcoVal", " (c/kW)", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("widgetEcoVal", " (c/anno)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox_5->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupBox_5->setTitle(QApplication::translate("widgetEcoVal", "Tariffe Misura", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("widgetEcoVal", " (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_63->setText(QApplication::translate("widgetEcoVal", " (c/kW)", 0, QApplication::UnicodeUTF8));
        label_64->setText(QApplication::translate("widgetEcoVal", " (c/anno)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupDisp->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupDisp->setTitle(QApplication::translate("widgetEcoVal", "Tariffe Dispacciamento", 0, QApplication::UnicodeUTF8));
        label_61->setText(QApplication::translate("widgetEcoVal", " (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_62->setText(QApplication::translate("widgetEcoVal", " (c/kW)", 0, QApplication::UnicodeUTF8));
        label_60->setText(QApplication::translate("widgetEcoVal", " (c/anno)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupGenerali->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupGenerali->setTitle(QApplication::translate("widgetEcoVal", "Tariffe per oneri generali", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("widgetEcoVal", "(c/kWh)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dAUCkWh->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_12->setText(QApplication::translate("widgetEcoVal", "(c/kW)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dAUCkW->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_22->setText(QApplication::translate("widgetEcoVal", "(c/anno)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dAUCanno->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_78->setToolTip(QApplication::translate("widgetEcoVal", "<p> MCT &egrave; una tariffa che non rimborsabile in regime di scambio. </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_78->setText(QApplication::translate("widgetEcoVal", "MCT (c/kWh)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupCoeffVendita->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        groupCoeffVendita->setTitle(QApplication::translate("widgetEcoVal", "Coefficienti per produttori", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_31->setToolTip(QApplication::translate("widgetEcoVal", "<p>Coefficiente del corrisp. passivo di trasmissione</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_31->setText(QApplication::translate("widgetEcoVal", "Coeff. Trasmissione (c/kWh)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dPerditaTrasmissione->setToolTip(QApplication::translate("widgetEcoVal", "<p>Coefficiente del corrisp. passivo di trasmissione</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_34->setToolTip(QApplication::translate("widgetEcoVal", "<p>Corrispettivo CTR</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_34->setText(QApplication::translate("widgetEcoVal", "CTR(c/kWh)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dCTRkWh->setToolTip(QApplication::translate("widgetEcoVal", "<p>Corrispettivo CTR</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_36->setToolTip(QApplication::translate("widgetEcoVal", "<p>Coefficiente moltiplicativo relativo al CTR dell'energia immessa</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_36->setText(QApplication::translate("widgetEcoVal", "Fattore di perdita CTR ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_35->setToolTip(QApplication::translate("widgetEcoVal", "<p>Altri costi fissi quali Misura </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_35->setText(QApplication::translate("widgetEcoVal", "Altri costi mensili", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dAltriCostiMensili->setToolTip(QApplication::translate("widgetEcoVal", "<p>Altri costi fissi quali Misura </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        dCostiAmm->setToolTip(QApplication::translate("widgetEcoVal", "<p> Percentuale del controvalore dell'energia ritirata imputata come costo amministrativo</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_79->setToolTip(QApplication::translate("widgetEcoVal", "<p> Percentuale del controvalore dell'energia ritirata imputata come costo amministrativo</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_79->setText(QApplication::translate("widgetEcoVal", "Costi amministrativi (%)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_80->setToolTip(QApplication::translate("widgetEcoVal", "<p>Limite dei costi amministrativi </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_80->setText(QApplication::translate("widgetEcoVal", "Limite costi amm.", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dLimitCostiAmm->setToolTip(QApplication::translate("widgetEcoVal", "<p>Limite dei costi amministrativi </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        dFattCTR->setToolTip(QApplication::translate("widgetEcoVal", "<p>Coefficiente moltiplicativo relativo al CTR dell'energia immessa</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_56->setText(QApplication::translate("widgetEcoVal", "File recenti", 0, QApplication::UnicodeUTF8));
        pushCutOneriFile->setText(QApplication::translate("widgetEcoVal", "Elimina", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushSavePrezziAs->setToolTip(QApplication::translate("widgetEcoVal", "<p>Salva gli oneri su file</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushSavePrezziAs->setText(QApplication::translate("widgetEcoVal", "Salva come", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushSavePrezzi->setToolTip(QApplication::translate("widgetEcoVal", "<p>Salva gli oneri sul file corrente</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushSavePrezzi->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushLoadPrezzi->setToolTip(QApplication::translate("widgetEcoVal", "<p> Carica da file i dati delle tariffe</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushLoadPrezzi->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushInfoTariffe->setToolTip(QApplication::translate("widgetEcoVal", "<p>Informazioni sulla tipologia dei dati tariffari</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushInfoTariffe->setText(QApplication::translate("widgetEcoVal", "Info", 0, QApplication::UnicodeUTF8));
        label_65->setText(QApplication::translate("widgetEcoVal", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS UI Gothic'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">NOTE:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">1) A tutte le tariffe viene applicata l'IVA di Costo Energia per Fasce orarie</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margi"
                        "n-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt; font-weight:600;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">2) Tutti valori monetari sono espressi </span><span style=\" font-size:10pt; font-weight:600; text-decoration: underline;\">nell'Unit\303\240 Monetaria (UM) corrente</span><span style=\" font-size:10pt; font-weight:600;\">, salvo ove indicato il simbolo di centesimi &quot;c&quot;</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        groupPrezzi->setTitle(QApplication::translate("widgetEcoVal", "Prezzi energia immessa (c/kWh)", 0, QApplication::UnicodeUTF8));
        labelWarn->setText(QString());
        label_51->setText(QApplication::translate("widgetEcoVal", "Fascia oraria", 0, QApplication::UnicodeUTF8));
        comboImmBand->clear();
        comboImmBand->insertItems(0, QStringList()
         << QApplication::translate("widgetEcoVal", "B1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B1(sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B2(sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B3(sabato)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B1(domenica)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B2(dpmenica)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "B3(domenica)", 0, QApplication::UnicodeUTF8)
        );
        label_10->setText(QApplication::translate("widgetEcoVal", "MEMO", 0, QApplication::UnicodeUTF8));
        label_40->setText(QApplication::translate("widgetEcoVal", "Tasso infl. energia", 0, QApplication::UnicodeUTF8));
        radioSimpleInflation->setText(QApplication::translate("widgetEcoVal", "Semplice inflazione", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("widgetEcoVal", "File  recenti ", 0, QApplication::UnicodeUTF8));
        pushCutPrezziFile->setText(QApplication::translate("widgetEcoVal", "Elimina", 0, QApplication::UnicodeUTF8));
        pushSavePrezziEnergiaAs->setText(QApplication::translate("widgetEcoVal", "Salva come", 0, QApplication::UnicodeUTF8));
        pushSavePrezziEnergia->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
        pushLoadPrezziEnergia->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
        pushInfoPrezzi->setText(QApplication::translate("widgetEcoVal", "Info", 0, QApplication::UnicodeUTF8));
        groupMinPrices->setTitle(QApplication::translate("widgetEcoVal", "Prezzi di vendita (c/kWh)", 0, QApplication::UnicodeUTF8));
        checkImmIntervals->setText(QApplication::translate("widgetEcoVal", "Abilita Fasce di immissione", 0, QApplication::UnicodeUTF8));
        groupImmIntervals->setTitle(QApplication::translate("widgetEcoVal", "Prezzi garantiti per fasce di immisione", 0, QApplication::UnicodeUTF8));
        pushImmissione->setText(QString());
        label_33->setText(QApplication::translate("widgetEcoVal", "Prezzo unico annuale(c/MWh)", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("widgetEcoVal", "Prezzi minimi garantiti mensili (c/kWh)", 0, QApplication::UnicodeUTF8));
        radioGARCH_2->setText(QApplication::translate("widgetEcoVal", "Usa modello GARCH", 0, QApplication::UnicodeUTF8));
        label_41->setText(QApplication::translate("widgetEcoVal", "Coeff. GARCH A1", 0, QApplication::UnicodeUTF8));
        label_42->setText(QApplication::translate("widgetEcoVal", "Coeff. GARCH B1", 0, QApplication::UnicodeUTF8));
        label_43->setText(QApplication::translate("widgetEcoVal", "Coeff. GARCH O1", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("widgetEcoVal", "Coeff. GARCH Mu", 0, QApplication::UnicodeUTF8));
        radioSimpleInflation_2->setText(QApplication::translate("widgetEcoVal", "Semplice inflazione", 0, QApplication::UnicodeUTF8));
        label_45->setText(QApplication::translate("widgetEcoVal", "Tasso infl. energia", 0, QApplication::UnicodeUTF8));
        groupBoxPM->setTitle(QApplication::translate("widgetEcoVal", "File recenti prezzi minimi mensili", 0, QApplication::UnicodeUTF8));
        pushCutMinPrezziFile->setText(QApplication::translate("widgetEcoVal", "Elimina", 0, QApplication::UnicodeUTF8));
        pushSaveMinPrezziEnergiaAs->setText(QApplication::translate("widgetEcoVal", "Salva come", 0, QApplication::UnicodeUTF8));
        pushSaveMinPrezziEnergia->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
        pushLoadMinPrezziEnergia->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
        pushInfoPrezziMinimi->setText(QApplication::translate("widgetEcoVal", "Info", 0, QApplication::UnicodeUTF8));
        labelWarnMin->setText(QString());
        groupBox_3->setTitle(QApplication::translate("widgetEcoVal", "Regime", 0, QApplication::UnicodeUTF8));
        comboRegime->clear();
        comboRegime->insertItems(0, QStringList()
         << QApplication::translate("widgetEcoVal", "Vendita", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetEcoVal", "SSP Italia", 0, QApplication::UnicodeUTF8)
        );
        checkCredit->setText(QApplication::translate("widgetEcoVal", "Liquidazione crediti", 0, QApplication::UnicodeUTF8));
        label_58->setText(QApplication::translate("widgetEcoVal", "Potenza contrattuale", 0, QApplication::UnicodeUTF8));
        label_59->setText(QApplication::translate("widgetEcoVal", "kW", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox_2->setToolTip(QApplication::translate("widgetEcoVal", "<p>I valori monetari non percentuali sono intesi nell'unit&agrave; monetaria corrente.</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_2->setTitle(QApplication::translate("widgetEcoVal", "Variabili di investimento", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("widgetEcoVal", "Costo iniziale (IVA esclusa)", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("widgetEcoVal", "Incentivi (c/kWh)", 0, QApplication::UnicodeUTF8));
        label_57->setText(QApplication::translate("widgetEcoVal", "anni", 0, QApplication::UnicodeUTF8));
        label_52->setText(QApplication::translate("widgetEcoVal", "IVA costo impianto (%)", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("widgetEcoVal", "Incentivi (c/kWp)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_28->setToolTip(QApplication::translate("widgetEcoVal", "<p> L'IVA viene calcolata automaticamente tenendo conto anche degli sgravi su IVA </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_28->setText(QApplication::translate("widgetEcoVal", "Finanziamento", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("widgetEcoVal", "anni", 0, QApplication::UnicodeUTF8));
        label_84->setText(QApplication::translate("widgetEcoVal", "il programma aggiunge l'IVA versata effettivamente", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("widgetEcoVal", "Tasso inflazione(%)", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("widgetEcoVal", "Tasso interesse Finanziamento(%)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("widgetEcoVal", "<p>Tasso attivo del capitale di investimento </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("widgetEcoVal", "Tasso di sconto(%)", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("widgetEcoVal", "Periodo d'analisi", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupBox->setToolTip(QApplication::translate("widgetEcoVal", "<p>I valori monetari non percentuali sono intesi nell'unit&agrave; monetaria corrente.</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("widgetEcoVal", "Costi fissi", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("widgetEcoVal", "Manutenzione annuale", 0, QApplication::UnicodeUTF8));
        label_47->setText(QApplication::translate("widgetEcoVal", "Manutenzione straordinaria", 0, QApplication::UnicodeUTF8));
        label_48->setText(QApplication::translate("widgetEcoVal", "Frequenza manut. s.", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("widgetEcoVal", "Affitti/anno", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("widgetEcoVal", "Altro", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("widgetEcoVal", "Assicurazione x kWp", 0, QApplication::UnicodeUTF8));
        label_55->setText(QApplication::translate("widgetEcoVal", "anni", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("widgetEcoVal", "Sgravi fiscali", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("widgetEcoVal", "% su interessi passivi", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("widgetEcoVal", "% sgravi (RIB,Ammort,costi)", 0, QApplication::UnicodeUTF8));
        label_53->setText(QApplication::translate("widgetEcoVal", "Ammortamento (%)", 0, QApplication::UnicodeUTF8));
        label_49->setText(QApplication::translate("widgetEcoVal", "% su IVA iniziale", 0, QApplication::UnicodeUTF8));
        label_83->setText(QApplication::translate("widgetEcoVal", "% spese iniziali", 0, QApplication::UnicodeUTF8));
        groupTax->setTitle(QApplication::translate("widgetEcoVal", "Imposte", 0, QApplication::UnicodeUTF8));
        label_67->setText(QApplication::translate("widgetEcoVal", "Incentivo", 0, QApplication::UnicodeUTF8));
        label_68->setText(QApplication::translate("widgetEcoVal", "Contributo CS", 0, QApplication::UnicodeUTF8));
        label_69->setText(QApplication::translate("widgetEcoVal", "Vendita energia", 0, QApplication::UnicodeUTF8));
        label_70->setText(QApplication::translate("widgetEcoVal", "IVA(%)", 0, QApplication::UnicodeUTF8));
        label_71->setText(QApplication::translate("widgetEcoVal", "IRPEF(%)", 0, QApplication::UnicodeUTF8));
        label_72->setText(QApplication::translate("widgetEcoVal", "IRAP(%)", 0, QApplication::UnicodeUTF8));
        label_73->setText(QApplication::translate("widgetEcoVal", "IRES(%)", 0, QApplication::UnicodeUTF8));
        label_75->setText(QApplication::translate("widgetEcoVal", "Altro (%)", 0, QApplication::UnicodeUTF8));
        label_74->setText(QApplication::translate("widgetEcoVal", "File recenti", 0, QApplication::UnicodeUTF8));
        pushCutTaxFile->setText(QApplication::translate("widgetEcoVal", "Elimina", 0, QApplication::UnicodeUTF8));
        pushSaveTax->setText(QApplication::translate("widgetEcoVal", "Salva", 0, QApplication::UnicodeUTF8));
        pushSaveTaxAs->setText(QApplication::translate("widgetEcoVal", "Salva come", 0, QApplication::UnicodeUTF8));
        pushLoadTax->setText(QApplication::translate("widgetEcoVal", "Carica", 0, QApplication::UnicodeUTF8));
        pushInfoTax->setText(QApplication::translate("widgetEcoVal", "Info", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class widgetEcoVal: public Ui_widgetEcoVal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECOVAL_H
