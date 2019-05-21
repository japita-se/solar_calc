/********************************************************************************
** Form generated from reading UI file 'addpv.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPV_H
#define UI_ADDPV_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddPV
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QDoubleSpinBox *dSpinBoxH;
    QDoubleSpinBox *dSpinBoxL;
    QDoubleSpinBox *dSpinBoxS;
    QGroupBox *groupParElettriciPannello;
    QSpinBox *spinBoxTolleranza;
    QDoubleSpinBox *dSpinBoxVoc;
    QDoubleSpinBox *dSpinBoxIsc;
    QDoubleSpinBox *dSpinBoxVmp;
    QLineEdit *linePeso;
    QDoubleSpinBox *dSpinBoxPnom;
    QDoubleSpinBox *dSpinBoxVmax;
    QDoubleSpinBox *dSpinBoxImp;
    QLabel *label_9;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *labelPnom;
    QLabel *label_10;
    QLabel *label_17;
    QLabel *label_7;
    QDoubleSpinBox *dSpinBoxBeta;
    QDoubleSpinBox *dSpinBoxGamma;
    QLabel *label_3;
    QDoubleSpinBox *dSpinBoxNoct;
    QLabel *label_18;
    QLabel *label_8;
    QLabel *label_14;
    QDoubleSpinBox *dSpinBoxVnom;
    QLabel *label_16;
    QLabel *label_19;
    QDoubleSpinBox *dSpinBoxAlfa;
    QLabel *label_15;
    QLabel *label_20;
    QDoubleSpinBox *dSpinBoxEff;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QDoubleSpinBox *dSpinBoxUsura;
    QLabel *label_42;
    QLabel *label_43;
    QLineEdit *lineModello;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineCostruttore;
    QCheckBox *checkDimensioni;
    QWidget *tab_2;
    QLabel *label_27;
    QLabel *label_28;
    QLineEdit *lineInverterCostruttore;
    QLineEdit *lineInverterModello;
    QGroupBox *groupParElettriciInverter;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_26;
    QDoubleSpinBox *dSpinBoxInvPin;
    QLabel *label_30;
    QLabel *label_22;
    QDoubleSpinBox *dSpinBoxInvVmax;
    QLabel *label_31;
    QLabel *label_21;
    QDoubleSpinBox *dSpinBoxInvVmin;
    QLabel *label_32;
    QLabel *label_23;
    QDoubleSpinBox *dSpinBoxInvVmpmin;
    QLabel *label_33;
    QLabel *label_24;
    QDoubleSpinBox *dSpinBoxInvVmpmax;
    QLabel *label_34;
    QLabel *label_45;
    QDoubleSpinBox *dSpinBoxInvImax;
    QLabel *label_46;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QLabel *label_25;
    QDoubleSpinBox *dSpinBoxInvPnom;
    QLabel *label_29;
    QLabel *label_37;
    QDoubleSpinBox *dSpinBoxInvEff;
    QLabel *label_38;
    QSpacerItem *verticalSpacer;
    QDoubleSpinBox *dSpinBoxInvUsura;
    QLabel *label_44;
    QLabel *label_47;
    QRadioButton *radioTM;
    QRadioButton *radioTT;
    QLabel *label_6;
    QLabel *label_48;
    QLabel *label_49;
    QDoubleSpinBox *dSpinIcc;
    QDoubleSpinBox *dSpinVout;
    QLabel *label_50;
    QLabel *label_51;
    QLabel *label_53;
    QCheckBox *checkTra;
    QLabel *label_52;
    QDoubleSpinBox *dSpinCosPhi;
    QPushButton *pushOk;
    QPushButton *pushCancel;

    void setupUi(QDialog *AddPV)
    {
        if (AddPV->objectName().isEmpty())
            AddPV->setObjectName(QString::fromUtf8("AddPV"));
        AddPV->resize(619, 592);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddPV->sizePolicy().hasHeightForWidth());
        AddPV->setSizePolicy(sizePolicy);
        AddPV->setMaximumSize(QSize(619, 592));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/app.png"), QSize(), QIcon::Normal, QIcon::Off);
        AddPV->setWindowIcon(icon);
        AddPV->setSizeGripEnabled(false);
        tabWidget = new QTabWidget(AddPV);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 0, 597, 541));
        tabWidget->setMaximumSize(QSize(16777215, 603));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 440, 531, 61));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 30, 57, 18));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(230, 30, 51, 20));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(400, 30, 57, 18));
        dSpinBoxH = new QDoubleSpinBox(groupBox);
        dSpinBoxH->setObjectName(QString::fromUtf8("dSpinBoxH"));
        dSpinBoxH->setGeometry(QRect(50, 30, 131, 23));
        dSpinBoxL = new QDoubleSpinBox(groupBox);
        dSpinBoxL->setObjectName(QString::fromUtf8("dSpinBoxL"));
        dSpinBoxL->setGeometry(QRect(250, 30, 121, 23));
        dSpinBoxS = new QDoubleSpinBox(groupBox);
        dSpinBoxS->setObjectName(QString::fromUtf8("dSpinBoxS"));
        dSpinBoxS->setGeometry(QRect(420, 30, 101, 23));
        groupParElettriciPannello = new QGroupBox(tab);
        groupParElettriciPannello->setObjectName(QString::fromUtf8("groupParElettriciPannello"));
        groupParElettriciPannello->setGeometry(QRect(10, 70, 541, 331));
        spinBoxTolleranza = new QSpinBox(groupParElettriciPannello);
        spinBoxTolleranza->setObjectName(QString::fromUtf8("spinBoxTolleranza"));
        spinBoxTolleranza->setGeometry(QRect(340, 260, 111, 23));
        spinBoxTolleranza->setMaximum(100);
        dSpinBoxVoc = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxVoc->setObjectName(QString::fromUtf8("dSpinBoxVoc"));
        dSpinBoxVoc->setGeometry(QRect(70, 80, 111, 23));
        dSpinBoxVoc->setMaximum(1e+06);
        dSpinBoxIsc = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxIsc->setObjectName(QString::fromUtf8("dSpinBoxIsc"));
        dSpinBoxIsc->setGeometry(QRect(70, 150, 111, 23));
        dSpinBoxIsc->setMaximum(1e+07);
        dSpinBoxVmp = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxVmp->setObjectName(QString::fromUtf8("dSpinBoxVmp"));
        dSpinBoxVmp->setGeometry(QRect(340, 50, 111, 23));
        dSpinBoxVmp->setDecimals(4);
        dSpinBoxVmp->setMaximum(1e+07);
        linePeso = new QLineEdit(groupParElettriciPannello);
        linePeso->setObjectName(QString::fromUtf8("linePeso"));
        linePeso->setGeometry(QRect(70, 260, 113, 23));
        dSpinBoxPnom = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxPnom->setObjectName(QString::fromUtf8("dSpinBoxPnom"));
        dSpinBoxPnom->setGeometry(QRect(70, 50, 111, 23));
        dSpinBoxPnom->setMaximum(1e+06);
        dSpinBoxVmax = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxVmax->setObjectName(QString::fromUtf8("dSpinBoxVmax"));
        dSpinBoxVmax->setGeometry(QRect(340, 80, 111, 23));
        dSpinBoxVmax->setDecimals(4);
        dSpinBoxVmax->setMaximum(1e+08);
        dSpinBoxImp = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxImp->setObjectName(QString::fromUtf8("dSpinBoxImp"));
        dSpinBoxImp->setGeometry(QRect(70, 180, 111, 23));
        dSpinBoxImp->setMaximum(1e+07);
        label_9 = new QLabel(groupParElettriciPannello);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(250, 80, 57, 18));
        label_4 = new QLabel(groupParElettriciPannello);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 110, 57, 18));
        label_5 = new QLabel(groupParElettriciPannello);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 150, 57, 18));
        labelPnom = new QLabel(groupParElettriciPannello);
        labelPnom->setObjectName(QString::fromUtf8("labelPnom"));
        labelPnom->setGeometry(QRect(20, 50, 57, 18));
        label_10 = new QLabel(groupParElettriciPannello);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(250, 50, 57, 18));
        label_17 = new QLabel(groupParElettriciPannello);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(250, 110, 91, 18));
        label_7 = new QLabel(groupParElettriciPannello);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 180, 57, 18));
        dSpinBoxBeta = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxBeta->setObjectName(QString::fromUtf8("dSpinBoxBeta"));
        dSpinBoxBeta->setGeometry(QRect(340, 110, 111, 23));
        dSpinBoxBeta->setDecimals(4);
        dSpinBoxBeta->setMaximum(100);
        dSpinBoxGamma = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxGamma->setObjectName(QString::fromUtf8("dSpinBoxGamma"));
        dSpinBoxGamma->setGeometry(QRect(340, 180, 111, 23));
        dSpinBoxGamma->setMaximum(100);
        label_3 = new QLabel(groupParElettriciPannello);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 80, 57, 18));
        dSpinBoxNoct = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxNoct->setObjectName(QString::fromUtf8("dSpinBoxNoct"));
        dSpinBoxNoct->setGeometry(QRect(70, 220, 111, 23));
        label_18 = new QLabel(groupParElettriciPannello);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(250, 160, 57, 18));
        label_8 = new QLabel(groupParElettriciPannello);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 220, 57, 18));
        label_14 = new QLabel(groupParElettriciPannello);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(250, 260, 71, 18));
        dSpinBoxVnom = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxVnom->setObjectName(QString::fromUtf8("dSpinBoxVnom"));
        dSpinBoxVnom->setGeometry(QRect(70, 110, 111, 23));
        dSpinBoxVnom->setMaximum(1e+07);
        label_16 = new QLabel(groupParElettriciPannello);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(20, 260, 57, 18));
        label_19 = new QLabel(groupParElettriciPannello);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(250, 180, 91, 18));
        dSpinBoxAlfa = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxAlfa->setObjectName(QString::fromUtf8("dSpinBoxAlfa"));
        dSpinBoxAlfa->setGeometry(QRect(340, 150, 111, 23));
        dSpinBoxAlfa->setDecimals(4);
        dSpinBoxAlfa->setMaximum(100);
        label_15 = new QLabel(groupParElettriciPannello);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(460, 110, 57, 18));
        label_20 = new QLabel(groupParElettriciPannello);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(460, 150, 57, 18));
        dSpinBoxEff = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxEff->setObjectName(QString::fromUtf8("dSpinBoxEff"));
        dSpinBoxEff->setGeometry(QRect(340, 230, 111, 23));
        dSpinBoxEff->setMaximum(100);
        label_35 = new QLabel(groupParElettriciPannello);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(250, 230, 89, 18));
        label_36 = new QLabel(groupParElettriciPannello);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(460, 230, 57, 18));
        label_39 = new QLabel(groupParElettriciPannello);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(460, 180, 57, 18));
        label_40 = new QLabel(groupParElettriciPannello);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(460, 260, 57, 18));
        label_41 = new QLabel(groupParElettriciPannello);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setGeometry(QRect(190, 260, 57, 18));
        dSpinBoxUsura = new QDoubleSpinBox(groupParElettriciPannello);
        dSpinBoxUsura->setObjectName(QString::fromUtf8("dSpinBoxUsura"));
        dSpinBoxUsura->setGeometry(QRect(340, 290, 111, 23));
        label_42 = new QLabel(groupParElettriciPannello);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        label_42->setGeometry(QRect(250, 290, 81, 31));
        label_42->setWordWrap(true);
        label_43 = new QLabel(groupParElettriciPannello);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setGeometry(QRect(460, 290, 57, 18));
        lineModello = new QLineEdit(tab);
        lineModello->setObjectName(QString::fromUtf8("lineModello"));
        lineModello->setGeometry(QRect(322, 30, 181, 23));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 91, 18));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 30, 57, 18));
        lineCostruttore = new QLineEdit(tab);
        lineCostruttore->setObjectName(QString::fromUtf8("lineCostruttore"));
        lineCostruttore->setGeometry(QRect(100, 30, 141, 23));
        checkDimensioni = new QCheckBox(tab);
        checkDimensioni->setObjectName(QString::fromUtf8("checkDimensioni"));
        checkDimensioni->setGeometry(QRect(10, 410, 181, 22));
        checkDimensioni->setChecked(true);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_27 = new QLabel(tab_2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(20, 30, 91, 18));
        label_28 = new QLabel(tab_2);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(260, 30, 57, 18));
        lineInverterCostruttore = new QLineEdit(tab_2);
        lineInverterCostruttore->setObjectName(QString::fromUtf8("lineInverterCostruttore"));
        lineInverterCostruttore->setGeometry(QRect(100, 30, 113, 23));
        lineInverterModello = new QLineEdit(tab_2);
        lineInverterModello->setObjectName(QString::fromUtf8("lineInverterModello"));
        lineInverterModello->setGeometry(QRect(330, 30, 113, 23));
        groupParElettriciInverter = new QGroupBox(tab_2);
        groupParElettriciInverter->setObjectName(QString::fromUtf8("groupParElettriciInverter"));
        groupParElettriciInverter->setGeometry(QRect(0, 80, 581, 421));
        gridLayout_3 = new QGridLayout(groupParElettriciInverter);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_2 = new QGroupBox(groupParElettriciInverter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"   \n"
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
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_2->addWidget(label_26, 0, 0, 1, 1);

        dSpinBoxInvPin = new QDoubleSpinBox(groupBox_2);
        dSpinBoxInvPin->setObjectName(QString::fromUtf8("dSpinBoxInvPin"));
        dSpinBoxInvPin->setMaximum(1e+09);

        gridLayout_2->addWidget(dSpinBoxInvPin, 0, 1, 1, 1);

        label_30 = new QLabel(groupBox_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_2->addWidget(label_30, 0, 2, 1, 1);

        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout_2->addWidget(label_22, 1, 0, 1, 1);

        dSpinBoxInvVmax = new QDoubleSpinBox(groupBox_2);
        dSpinBoxInvVmax->setObjectName(QString::fromUtf8("dSpinBoxInvVmax"));
        dSpinBoxInvVmax->setMaximum(1e+06);

        gridLayout_2->addWidget(dSpinBoxInvVmax, 1, 1, 1, 1);

        label_31 = new QLabel(groupBox_2);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout_2->addWidget(label_31, 1, 2, 1, 1);

        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_2->addWidget(label_21, 2, 0, 1, 1);

        dSpinBoxInvVmin = new QDoubleSpinBox(groupBox_2);
        dSpinBoxInvVmin->setObjectName(QString::fromUtf8("dSpinBoxInvVmin"));
        dSpinBoxInvVmin->setMaximum(1e+08);

        gridLayout_2->addWidget(dSpinBoxInvVmin, 2, 1, 1, 1);

        label_32 = new QLabel(groupBox_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_2->addWidget(label_32, 2, 2, 1, 1);

        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_2->addWidget(label_23, 3, 0, 1, 1);

        dSpinBoxInvVmpmin = new QDoubleSpinBox(groupBox_2);
        dSpinBoxInvVmpmin->setObjectName(QString::fromUtf8("dSpinBoxInvVmpmin"));
        dSpinBoxInvVmpmin->setMaximum(1e+08);

        gridLayout_2->addWidget(dSpinBoxInvVmpmin, 3, 1, 1, 1);

        label_33 = new QLabel(groupBox_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout_2->addWidget(label_33, 3, 2, 1, 1);

        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_2->addWidget(label_24, 4, 0, 1, 1);

        dSpinBoxInvVmpmax = new QDoubleSpinBox(groupBox_2);
        dSpinBoxInvVmpmax->setObjectName(QString::fromUtf8("dSpinBoxInvVmpmax"));
        dSpinBoxInvVmpmax->setMaximum(1e+09);

        gridLayout_2->addWidget(dSpinBoxInvVmpmax, 4, 1, 1, 1);

        label_34 = new QLabel(groupBox_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_2->addWidget(label_34, 4, 2, 1, 1);

        label_45 = new QLabel(groupBox_2);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        gridLayout_2->addWidget(label_45, 5, 0, 1, 1);

        dSpinBoxInvImax = new QDoubleSpinBox(groupBox_2);
        dSpinBoxInvImax->setObjectName(QString::fromUtf8("dSpinBoxInvImax"));
        dSpinBoxInvImax->setMaximum(1e+09);

        gridLayout_2->addWidget(dSpinBoxInvImax, 5, 1, 1, 1);

        label_46 = new QLabel(groupBox_2);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout_2->addWidget(label_46, 5, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(groupParElettriciInverter);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"   \n"
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
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout->addWidget(label_25, 0, 0, 1, 1);

        dSpinBoxInvPnom = new QDoubleSpinBox(groupBox_3);
        dSpinBoxInvPnom->setObjectName(QString::fromUtf8("dSpinBoxInvPnom"));
        dSpinBoxInvPnom->setMaximum(1e+09);

        gridLayout->addWidget(dSpinBoxInvPnom, 0, 1, 1, 1);

        label_29 = new QLabel(groupBox_3);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout->addWidget(label_29, 0, 2, 1, 1);

        label_37 = new QLabel(groupBox_3);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout->addWidget(label_37, 1, 0, 1, 1);

        dSpinBoxInvEff = new QDoubleSpinBox(groupBox_3);
        dSpinBoxInvEff->setObjectName(QString::fromUtf8("dSpinBoxInvEff"));
        dSpinBoxInvEff->setMaximum(100);

        gridLayout->addWidget(dSpinBoxInvEff, 1, 1, 1, 1);

        label_38 = new QLabel(groupBox_3);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout->addWidget(label_38, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 290, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 10, 1, 1, 1);

        dSpinBoxInvUsura = new QDoubleSpinBox(groupBox_3);
        dSpinBoxInvUsura->setObjectName(QString::fromUtf8("dSpinBoxInvUsura"));
        dSpinBoxInvUsura->setMaximum(100);

        gridLayout->addWidget(dSpinBoxInvUsura, 2, 1, 1, 1);

        label_44 = new QLabel(groupBox_3);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout->addWidget(label_44, 2, 0, 1, 1);

        label_47 = new QLabel(groupBox_3);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout->addWidget(label_47, 2, 2, 1, 1);

        radioTM = new QRadioButton(groupBox_3);
        radioTM->setObjectName(QString::fromUtf8("radioTM"));
        radioTM->setChecked(true);

        gridLayout->addWidget(radioTM, 5, 1, 1, 1);

        radioTT = new QRadioButton(groupBox_3);
        radioTT->setObjectName(QString::fromUtf8("radioTT"));

        gridLayout->addWidget(radioTT, 7, 1, 1, 1);

        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label_48 = new QLabel(groupBox_3);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout->addWidget(label_48, 3, 0, 1, 1);

        label_49 = new QLabel(groupBox_3);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        gridLayout->addWidget(label_49, 4, 0, 1, 1);

        dSpinIcc = new QDoubleSpinBox(groupBox_3);
        dSpinIcc->setObjectName(QString::fromUtf8("dSpinIcc"));
        dSpinIcc->setMaximum(1e+09);

        gridLayout->addWidget(dSpinIcc, 4, 1, 1, 1);

        dSpinVout = new QDoubleSpinBox(groupBox_3);
        dSpinVout->setObjectName(QString::fromUtf8("dSpinVout"));
        dSpinVout->setMaximum(1e+09);

        gridLayout->addWidget(dSpinVout, 3, 1, 1, 1);

        label_50 = new QLabel(groupBox_3);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        gridLayout->addWidget(label_50, 3, 2, 1, 1);

        label_51 = new QLabel(groupBox_3);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout->addWidget(label_51, 4, 2, 1, 1);

        label_53 = new QLabel(groupBox_3);
        label_53->setObjectName(QString::fromUtf8("label_53"));

        gridLayout->addWidget(label_53, 9, 0, 1, 1);

        checkTra = new QCheckBox(groupBox_3);
        checkTra->setObjectName(QString::fromUtf8("checkTra"));

        gridLayout->addWidget(checkTra, 9, 1, 1, 1);

        label_52 = new QLabel(groupBox_3);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        gridLayout->addWidget(label_52, 8, 0, 1, 1);

        dSpinCosPhi = new QDoubleSpinBox(groupBox_3);
        dSpinCosPhi->setObjectName(QString::fromUtf8("dSpinCosPhi"));
        dSpinCosPhi->setDecimals(4);
        dSpinCosPhi->setMaximum(1);

        gridLayout->addWidget(dSpinCosPhi, 8, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 0, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());
        pushOk = new QPushButton(AddPV);
        pushOk->setObjectName(QString::fromUtf8("pushOk"));
        pushOk->setGeometry(QRect(450, 560, 75, 27));
        pushCancel = new QPushButton(AddPV);
        pushCancel->setObjectName(QString::fromUtf8("pushCancel"));
        pushCancel->setGeometry(QRect(530, 560, 75, 27));
        QWidget::setTabOrder(lineCostruttore, lineModello);
        QWidget::setTabOrder(lineModello, dSpinBoxPnom);
        QWidget::setTabOrder(dSpinBoxPnom, dSpinBoxVoc);
        QWidget::setTabOrder(dSpinBoxVoc, dSpinBoxVnom);
        QWidget::setTabOrder(dSpinBoxVnom, dSpinBoxIsc);
        QWidget::setTabOrder(dSpinBoxIsc, dSpinBoxImp);
        QWidget::setTabOrder(dSpinBoxImp, dSpinBoxNoct);
        QWidget::setTabOrder(dSpinBoxNoct, linePeso);
        QWidget::setTabOrder(linePeso, dSpinBoxVmp);
        QWidget::setTabOrder(dSpinBoxVmp, dSpinBoxVmax);
        QWidget::setTabOrder(dSpinBoxVmax, dSpinBoxBeta);
        QWidget::setTabOrder(dSpinBoxBeta, dSpinBoxAlfa);
        QWidget::setTabOrder(dSpinBoxAlfa, dSpinBoxGamma);
        QWidget::setTabOrder(dSpinBoxGamma, dSpinBoxEff);
        QWidget::setTabOrder(dSpinBoxEff, spinBoxTolleranza);
        QWidget::setTabOrder(spinBoxTolleranza, dSpinBoxUsura);
        QWidget::setTabOrder(dSpinBoxUsura, checkDimensioni);
        QWidget::setTabOrder(checkDimensioni, dSpinBoxH);
        QWidget::setTabOrder(dSpinBoxH, dSpinBoxL);
        QWidget::setTabOrder(dSpinBoxL, dSpinBoxS);
        QWidget::setTabOrder(dSpinBoxS, pushOk);
        QWidget::setTabOrder(pushOk, pushCancel);
        QWidget::setTabOrder(pushCancel, lineInverterModello);
        QWidget::setTabOrder(lineInverterModello, tabWidget);
        QWidget::setTabOrder(tabWidget, lineInverterCostruttore);
        QWidget::setTabOrder(lineInverterCostruttore, dSpinBoxInvPin);
        QWidget::setTabOrder(dSpinBoxInvPin, dSpinBoxInvVmax);
        QWidget::setTabOrder(dSpinBoxInvVmax, dSpinBoxInvVmin);
        QWidget::setTabOrder(dSpinBoxInvVmin, dSpinBoxInvVmpmin);
        QWidget::setTabOrder(dSpinBoxInvVmpmin, dSpinBoxInvVmpmax);
        QWidget::setTabOrder(dSpinBoxInvVmpmax, dSpinBoxInvImax);
        QWidget::setTabOrder(dSpinBoxInvImax, dSpinBoxInvPnom);
        QWidget::setTabOrder(dSpinBoxInvPnom, dSpinBoxInvEff);
        QWidget::setTabOrder(dSpinBoxInvEff, dSpinBoxInvUsura);

        retranslateUi(AddPV);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AddPV);
    } // setupUi

    void retranslateUi(QDialog *AddPV)
    {
        AddPV->setWindowTitle(QApplication::translate("AddPV", "Inserimento componenti", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AddPV", "Dimensioni in mm", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("AddPV", "H", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("AddPV", "L", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("AddPV", "s", 0, QApplication::UnicodeUTF8));
        groupParElettriciPannello->setTitle(QApplication::translate("AddPV", "Parametri elettrici", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_9->setToolTip(QApplication::translate("AddPV", "<p> Tensione massima di sistema </P>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("AddPV", "Vmax", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("AddPV", "<p> Tensione nominale </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("AddPV", "Vnom", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("AddPV", "<p> Corrente di cortocircuito </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("AddPV", "Isc", 0, QApplication::UnicodeUTF8));
        labelPnom->setText(QApplication::translate("AddPV", "Pnom", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_10->setToolTip(QApplication::translate("AddPV", "<p> Tensione alla massima potenza </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_10->setText(QApplication::translate("AddPV", "Vmp", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_17->setToolTip(QApplication::translate("AddPV", "<p> Coefficienti di variazione Voc </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_17->setText(QApplication::translate("AddPV", "beta(Voc)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QApplication::translate("AddPV", "<p> Corrente alla massima potenza </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("AddPV", "Imp", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("AddPV", "<p> Tensione a circuito aperto </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("AddPV", "Voc", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_18->setToolTip(QApplication::translate("AddPV", "<p> Coefficienti di variazione Isc </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_18->setText(QApplication::translate("AddPV", "alfa(Isc)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_8->setToolTip(QApplication::translate("AddPV", "<p> Normal Operating Cell Temperature</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("AddPV", "NOCT", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_14->setToolTip(QApplication::translate("AddPV", "<p> Tolleranza percentuale sui dati di targa </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_14->setText(QApplication::translate("AddPV", "Tolleranza", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("AddPV", "Peso", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_19->setToolTip(QApplication::translate("AddPV", "<p> Coefficiente di variazione di Pnom </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_19->setText(QApplication::translate("AddPV", "gamma(Pnom)", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("AddPV", "%/grado", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("AddPV", "%/grado", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_35->setToolTip(QApplication::translate("AddPV", "<p>Efficienza del pannello</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_35->setText(QApplication::translate("AddPV", "Efficienza", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("AddPV", "%", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("AddPV", "%/grado", 0, QApplication::UnicodeUTF8));
        label_40->setText(QApplication::translate("AddPV", "%", 0, QApplication::UnicodeUTF8));
        label_41->setText(QApplication::translate("AddPV", "Kg", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_42->setToolTip(QApplication::translate("AddPV", "<p> Variazione annuale  effecienza dovuta a usura </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_42->setText(QApplication::translate("AddPV", "Usura annuale", 0, QApplication::UnicodeUTF8));
        label_43->setText(QApplication::translate("AddPV", "%", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddPV", "Costruttore", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddPV", "Modello", 0, QApplication::UnicodeUTF8));
        checkDimensioni->setText(QApplication::translate("AddPV", "Specifica dimensioni", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AddPV", "&Pannello", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("AddPV", "Costruttore", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("AddPV", "Modello", 0, QApplication::UnicodeUTF8));
        groupParElettriciInverter->setTitle(QApplication::translate("AddPV", "Parametri elettrici", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("AddPV", "Ingresso", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("AddPV", "Pin(max)", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("AddPV", "W", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("AddPV", "Vmax", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("AddPV", "V", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("AddPV", "Vmin", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("AddPV", "V", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("AddPV", "Vmp(min)", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("AddPV", "V", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("AddPV", "Vmp(max)", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("AddPV", "V", 0, QApplication::UnicodeUTF8));
        label_45->setText(QApplication::translate("AddPV", "I(max)", 0, QApplication::UnicodeUTF8));
        label_46->setText(QApplication::translate("AddPV", "A", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("AddPV", "Uscita", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("AddPV", "Pnom", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("AddPV", "Wp", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("AddPV", "Efficienza", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("AddPV", "%", 0, QApplication::UnicodeUTF8));
        label_44->setText(QApplication::translate("AddPV", "Usura annuale", 0, QApplication::UnicodeUTF8));
        label_47->setText(QApplication::translate("AddPV", "%", 0, QApplication::UnicodeUTF8));
        radioTM->setText(QApplication::translate("AddPV", "Monofase", 0, QApplication::UnicodeUTF8));
        radioTT->setText(QApplication::translate("AddPV", "Trifase", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("AddPV", "Tipo", 0, QApplication::UnicodeUTF8));
        label_48->setText(QApplication::translate("AddPV", "Tensione ca", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_49->setToolTip(QApplication::translate("AddPV", "Se non si conosce tale valore, moltiplicare per 1,5 il valore imax", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_49->setText(QApplication::translate("AddPV", "Contributo corrente cc", 0, QApplication::UnicodeUTF8));
        label_50->setText(QApplication::translate("AddPV", "V", 0, QApplication::UnicodeUTF8));
        label_51->setText(QApplication::translate("AddPV", "A", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_53->setToolTip(QApplication::translate("AddPV", "Trasformatore d'uscita presente?", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_53->setText(QApplication::translate("AddPV", "Trasformatore ", 0, QApplication::UnicodeUTF8));
        checkTra->setText(QApplication::translate("AddPV", "presente", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_52->setToolTip(QApplication::translate("AddPV", "Fattore di potenza in uscita ca", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_52->setText(QApplication::translate("AddPV", "cos PHI", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("AddPV", "&Inverter", 0, QApplication::UnicodeUTF8));
        pushOk->setText(QApplication::translate("AddPV", "OK", 0, QApplication::UnicodeUTF8));
        pushCancel->setText(QApplication::translate("AddPV", "Cancella", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddPV: public Ui_AddPV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPV_H
