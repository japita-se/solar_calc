/********************************************************************************
** Form generated from reading UI file 'consumi.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSUMI_H
#define UI_CONSUMI_H

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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_widgetConsumi
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QLabel *label_14;
    QLineEdit *lineAnnui;
    QLabel *label_7;
    QLabel *label_8;
    QComboBox *comboMonthly;
    QLabel *label_4;
    QDoubleSpinBox *dFactor;
    QwtPlot *qwtMonthly;
    QTableWidget *tableMonthly;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *label_15;
    QComboBox *comboHourly;
    QTableWidget *tableHourly;
    QwtPlot *qwtWeekly;
    QwtPlot *qwtHourly;
    QLabel *label;
    QDoubleSpinBox *dQuotaSabato;
    QCheckBox *checkNormSat;
    QLabel *label_3;
    QComboBox *comboChiusura;
    QLabel *label_2;
    QDoubleSpinBox *dQuotaDomenica;
    QCheckBox *checkNormSun;
    QGridLayout *gridLayout_2;
    QLabel *label_23;
    QLabel *labelTotal;
    QLabel *label_25;
    QLabel *labelTotalSat;
    QLabel *label_26;
    QLabel *labelTotalRest;
    QLabel *label_24;
    QLabel *labelTotalPercent;
    QLabel *labelWarningHours;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkCurrentMonths;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *buttonSaveAs;
    QPushButton *buttonSave;
    QPushButton *buttonCarica;
    QPushButton *pushApply;
    QPushButton *pushCancel;

    void setupUi(QWidget *widgetConsumi)
    {
        if (widgetConsumi->objectName().isEmpty())
            widgetConsumi->setObjectName(QString::fromUtf8("widgetConsumi"));
        widgetConsumi->resize(1167, 610);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetConsumi->sizePolicy().hasHeightForWidth());
        widgetConsumi->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/editorconsumi.png"), QSize(), QIcon::Normal, QIcon::Off);
        widgetConsumi->setWindowIcon(icon);
        gridLayout_5 = new QGridLayout(widgetConsumi);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(widgetConsumi);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMaximumSize(QSize(16777215, 300));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
"    \n"
"      \n"
" }"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 0, 0, 1, 1);

        lineAnnui = new QLineEdit(groupBox);
        lineAnnui->setObjectName(QString::fromUtf8("lineAnnui"));
        lineAnnui->setStyleSheet(QString::fromUtf8(" border: 2px solid gray;\n"
"     border-radius: 10px;\n"
"     padding: 0 8px;\n"
"     background: yellow;\n"
"     selection-background-color: darkgray;"));
        lineAnnui->setReadOnly(true);

        gridLayout->addWidget(lineAnnui, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 2, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 1, 0, 1, 1);

        comboMonthly = new QComboBox(groupBox);
        comboMonthly->setObjectName(QString::fromUtf8("comboMonthly"));

        gridLayout->addWidget(comboMonthly, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 3, 1, 1);

        dFactor = new QDoubleSpinBox(groupBox);
        dFactor->setObjectName(QString::fromUtf8("dFactor"));
        dFactor->setMinimum(1);

        gridLayout->addWidget(dFactor, 1, 4, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);

        qwtMonthly = new QwtPlot(groupBox);
        qwtMonthly->setObjectName(QString::fromUtf8("qwtMonthly"));
        sizePolicy.setHeightForWidth(qwtMonthly->sizePolicy().hasHeightForWidth());
        qwtMonthly->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(qwtMonthly, 0, 1, 2, 1);

        tableMonthly = new QTableWidget(groupBox);
        if (tableMonthly->columnCount() < 13)
            tableMonthly->setColumnCount(13);
        if (tableMonthly->rowCount() < 2)
            tableMonthly->setRowCount(2);
        tableMonthly->setObjectName(QString::fromUtf8("tableMonthly"));
        sizePolicy.setHeightForWidth(tableMonthly->sizePolicy().hasHeightForWidth());
        tableMonthly->setSizePolicy(sizePolicy);
        tableMonthly->setMaximumSize(QSize(16777215, 130));
        tableMonthly->setRowCount(2);
        tableMonthly->setColumnCount(13);

        gridLayout_4->addWidget(tableMonthly, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(widgetConsumi);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        groupBox_2->setMaximumSize(QSize(16777215, 800));
        groupBox_2->setFont(font);
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
"      \n"
" }"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setWordWrap(true);

        gridLayout_3->addWidget(label_15, 0, 0, 1, 1);

        comboHourly = new QComboBox(groupBox_2);
        comboHourly->setObjectName(QString::fromUtf8("comboHourly"));

        gridLayout_3->addWidget(comboHourly, 0, 1, 1, 2);

        tableHourly = new QTableWidget(groupBox_2);
        if (tableHourly->columnCount() < 2)
            tableHourly->setColumnCount(2);
        if (tableHourly->rowCount() < 24)
            tableHourly->setRowCount(24);
        tableHourly->setObjectName(QString::fromUtf8("tableHourly"));
        sizePolicy.setHeightForWidth(tableHourly->sizePolicy().hasHeightForWidth());
        tableHourly->setSizePolicy(sizePolicy);
        tableHourly->setMaximumSize(QSize(16777215, 400));
        tableHourly->setRowCount(24);
        tableHourly->setColumnCount(2);
        tableHourly->horizontalHeader()->setMinimumSectionSize(100);

        gridLayout_3->addWidget(tableHourly, 0, 3, 5, 1);

        qwtWeekly = new QwtPlot(groupBox_2);
        qwtWeekly->setObjectName(QString::fromUtf8("qwtWeekly"));
        sizePolicy.setHeightForWidth(qwtWeekly->sizePolicy().hasHeightForWidth());
        qwtWeekly->setSizePolicy(sizePolicy);
        qwtWeekly->setMinimumSize(QSize(200, 0));

        gridLayout_3->addWidget(qwtWeekly, 0, 4, 5, 1);

        qwtHourly = new QwtPlot(groupBox_2);
        qwtHourly->setObjectName(QString::fromUtf8("qwtHourly"));
        sizePolicy.setHeightForWidth(qwtHourly->sizePolicy().hasHeightForWidth());
        qwtHourly->setSizePolicy(sizePolicy);
        qwtHourly->setMinimumSize(QSize(200, 0));

        gridLayout_3->addWidget(qwtHourly, 0, 5, 5, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 1, 0, 1, 1);

        dQuotaSabato = new QDoubleSpinBox(groupBox_2);
        dQuotaSabato->setObjectName(QString::fromUtf8("dQuotaSabato"));
        dQuotaSabato->setDecimals(4);

        gridLayout_3->addWidget(dQuotaSabato, 1, 1, 1, 1);

        checkNormSat = new QCheckBox(groupBox_2);
        checkNormSat->setObjectName(QString::fromUtf8("checkNormSat"));

        gridLayout_3->addWidget(checkNormSat, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        comboChiusura = new QComboBox(groupBox_2);
        comboChiusura->setObjectName(QString::fromUtf8("comboChiusura"));
        comboChiusura->setMinimumSize(QSize(100, 0));

        gridLayout_3->addWidget(comboChiusura, 2, 1, 1, 2);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 3, 0, 1, 1);

        dQuotaDomenica = new QDoubleSpinBox(groupBox_2);
        dQuotaDomenica->setObjectName(QString::fromUtf8("dQuotaDomenica"));
        dQuotaDomenica->setDecimals(4);
        dQuotaDomenica->setMaximum(100);

        gridLayout_3->addWidget(dQuotaDomenica, 3, 1, 1, 1);

        checkNormSun = new QCheckBox(groupBox_2);
        checkNormSun->setObjectName(QString::fromUtf8("checkNormSun"));

        gridLayout_3->addWidget(checkNormSun, 3, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setWordWrap(true);

        gridLayout_2->addWidget(label_23, 0, 0, 1, 1);

        labelTotal = new QLabel(groupBox_2);
        labelTotal->setObjectName(QString::fromUtf8("labelTotal"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelTotal->sizePolicy().hasHeightForWidth());
        labelTotal->setSizePolicy(sizePolicy1);
        labelTotal->setMinimumSize(QSize(20, 0));
        labelTotal->setMaximumSize(QSize(400, 16777215));
        labelTotal->setFrameShape(QFrame::Panel);

        gridLayout_2->addWidget(labelTotal, 0, 1, 1, 1);

        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setWordWrap(true);

        gridLayout_2->addWidget(label_25, 1, 0, 1, 1);

        labelTotalSat = new QLabel(groupBox_2);
        labelTotalSat->setObjectName(QString::fromUtf8("labelTotalSat"));
        sizePolicy1.setHeightForWidth(labelTotalSat->sizePolicy().hasHeightForWidth());
        labelTotalSat->setSizePolicy(sizePolicy1);
        labelTotalSat->setMinimumSize(QSize(20, 0));
        labelTotalSat->setMaximumSize(QSize(400, 16777215));
        labelTotalSat->setFrameShape(QFrame::Panel);

        gridLayout_2->addWidget(labelTotalSat, 1, 1, 1, 1);

        label_26 = new QLabel(groupBox_2);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setWordWrap(true);

        gridLayout_2->addWidget(label_26, 2, 0, 1, 1);

        labelTotalRest = new QLabel(groupBox_2);
        labelTotalRest->setObjectName(QString::fromUtf8("labelTotalRest"));
        sizePolicy1.setHeightForWidth(labelTotalRest->sizePolicy().hasHeightForWidth());
        labelTotalRest->setSizePolicy(sizePolicy1);
        labelTotalRest->setMinimumSize(QSize(20, 0));
        labelTotalRest->setMaximumSize(QSize(400, 16777215));
        labelTotalRest->setFrameShape(QFrame::Panel);

        gridLayout_2->addWidget(labelTotalRest, 2, 1, 1, 1);

        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        gridLayout_2->addWidget(label_24, 3, 0, 1, 1);

        labelTotalPercent = new QLabel(groupBox_2);
        labelTotalPercent->setObjectName(QString::fromUtf8("labelTotalPercent"));
        sizePolicy1.setHeightForWidth(labelTotalPercent->sizePolicy().hasHeightForWidth());
        labelTotalPercent->setSizePolicy(sizePolicy1);
        labelTotalPercent->setMinimumSize(QSize(20, 0));
        labelTotalPercent->setMaximumSize(QSize(400, 16777215));
        labelTotalPercent->setFrameShape(QFrame::Panel);

        gridLayout_2->addWidget(labelTotalPercent, 3, 1, 1, 1);

        labelWarningHours = new QLabel(groupBox_2);
        labelWarningHours->setObjectName(QString::fromUtf8("labelWarningHours"));
        labelWarningHours->setMinimumSize(QSize(0, 0));
        labelWarningHours->setMaximumSize(QSize(400, 16777215));
        labelWarningHours->setWordWrap(true);

        gridLayout_2->addWidget(labelWarningHours, 4, 0, 1, 2);


        gridLayout_3->addLayout(gridLayout_2, 4, 0, 1, 3);


        gridLayout_5->addWidget(groupBox_2, 1, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        checkCurrentMonths = new QCheckBox(widgetConsumi);
        checkCurrentMonths->setObjectName(QString::fromUtf8("checkCurrentMonths"));

        horizontalLayout_8->addWidget(checkCurrentMonths);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);

        buttonSaveAs = new QPushButton(widgetConsumi);
        buttonSaveAs->setObjectName(QString::fromUtf8("buttonSaveAs"));

        horizontalLayout_8->addWidget(buttonSaveAs);

        buttonSave = new QPushButton(widgetConsumi);
        buttonSave->setObjectName(QString::fromUtf8("buttonSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonSave->setIcon(icon1);

        horizontalLayout_8->addWidget(buttonSave);

        buttonCarica = new QPushButton(widgetConsumi);
        buttonCarica->setObjectName(QString::fromUtf8("buttonCarica"));
        buttonCarica->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCarica->setIcon(icon2);

        horizontalLayout_8->addWidget(buttonCarica);

        pushApply = new QPushButton(widgetConsumi);
        pushApply->setObjectName(QString::fromUtf8("pushApply"));

        horizontalLayout_8->addWidget(pushApply);

        pushCancel = new QPushButton(widgetConsumi);
        pushCancel->setObjectName(QString::fromUtf8("pushCancel"));

        horizontalLayout_8->addWidget(pushCancel);


        gridLayout_5->addLayout(horizontalLayout_8, 2, 0, 1, 1);


        retranslateUi(widgetConsumi);

        QMetaObject::connectSlotsByName(widgetConsumi);
    } // setupUi

    void retranslateUi(QWidget *widgetConsumi)
    {
        widgetConsumi->setWindowTitle(QApplication::translate("widgetConsumi", "Consumi elettrici", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("widgetConsumi", "Consumi annuali e distribuzione mensile", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("widgetConsumi", "Annui", 0, QApplication::UnicodeUTF8));
        lineAnnui->setText(QApplication::translate("widgetConsumi", "0", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("widgetConsumi", "kWh", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("widgetConsumi", "Mensili", 0, QApplication::UnicodeUTF8));
        comboMonthly->clear();
        comboMonthly->insertItems(0, QStringList()
         << QApplication::translate("widgetConsumi", "Uniformi", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Stagionali/Estate", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Stagionali/Inverno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Ciclico/Inverno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Ciclico/Estate", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Custom", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("widgetConsumi", "Fattore amp.", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("widgetConsumi", "Ripartizione settimanale e profili orari", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("widgetConsumi", "Profilo carichi orari", 0, QApplication::UnicodeUTF8));
        comboHourly->clear();
        comboHourly->insertItems(0, QStringList()
         << QApplication::translate("widgetConsumi", "Uniformi", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Residenziale", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Custom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Commerciale", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Industriale", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("widgetConsumi", "<p>Quota percentuale di consumo mensile nei giorni di sabato rispetto ai giorni feriali</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("widgetConsumi", "% sabato", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkNormSat->setToolTip(QApplication::translate("widgetConsumi", "<p>Rende la quota di sabato uguale alla quota dei giorni feriali </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkNormSat->setText(QApplication::translate("widgetConsumi", "Equalizza", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("widgetConsumi", "Giorno chiusura", 0, QApplication::UnicodeUTF8));
        comboChiusura->clear();
        comboChiusura->insertItems(0, QStringList()
         << QApplication::translate("widgetConsumi", "Nessuno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Dom", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Lun", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Mar", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Mer", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Gio", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("widgetConsumi", "Ven", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("widgetConsumi", "<p>Quota percentuale di consumo mensile nei giorni di chiusura rispetto ai giorni feriali</p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("widgetConsumi", "% giorno chiusura", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        checkNormSun->setToolTip(QApplication::translate("widgetConsumi", "<p>Rende la quota del giorno di chiusura uguale alla quota dei giorni feriali </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        checkNormSun->setText(QApplication::translate("widgetConsumi", "Equalizza", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("widgetConsumi", "Energia giornaliera feriale (kWh)", 0, QApplication::UnicodeUTF8));
        labelTotal->setText(QApplication::translate("widgetConsumi", "0", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("widgetConsumi", "Energia giornaliera sabato (kWh)", 0, QApplication::UnicodeUTF8));
        labelTotalSat->setText(QApplication::translate("widgetConsumi", "0", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("widgetConsumi", "Energia giornaliera chiusura (kWh)", 0, QApplication::UnicodeUTF8));
        labelTotalRest->setText(QApplication::translate("widgetConsumi", "0", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("widgetConsumi", "Totale (%)", 0, QApplication::UnicodeUTF8));
        labelTotalPercent->setText(QApplication::translate("widgetConsumi", "0", 0, QApplication::UnicodeUTF8));
        labelWarningHours->setText(QString());
        checkCurrentMonths->setText(QApplication::translate("widgetConsumi", "Salva solo il mese corrente", 0, QApplication::UnicodeUTF8));
        buttonSaveAs->setText(QApplication::translate("widgetConsumi", "Salva come...", 0, QApplication::UnicodeUTF8));
        buttonSave->setText(QApplication::translate("widgetConsumi", "Salva", 0, QApplication::UnicodeUTF8));
        buttonCarica->setText(QApplication::translate("widgetConsumi", "Carica", 0, QApplication::UnicodeUTF8));
        pushApply->setText(QApplication::translate("widgetConsumi", "Applica", 0, QApplication::UnicodeUTF8));
        pushCancel->setText(QApplication::translate("widgetConsumi", "Annulla", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class widgetConsumi: public Ui_widgetConsumi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSUMI_H
