/********************************************************************************
** Form generated from reading ui file 'consumi.ui'
**
** Created: Tue Jul 21 09:29:35 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef CONSUMI_H
#define CONSUMI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_dialogConsumi
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tabConsumi;
    QGroupBox *groupBox;
    QLabel *label_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *annuiDSpin;
    QLabel *label_2;
    QTableWidget *tableMonthly;
    QComboBox *comboMonthly;
    QLabel *label_6;
    QLabel *labelWarning;
    QLabel *label_3;
    QTableWidget *tableHourly;
    QwtPlot *plotHourly;
    QComboBox *comboHourly;
    QLabel *label_5;
    QLabel *labelTotal;
    QLabel *labelWarningHours;
    QLabel *labelTotalPercent;
    QPushButton *buttonSave;
    QPushButton *buttonCarica;

    void setupUi(QDialog *dialogConsumi)
    {
        if (dialogConsumi->objectName().isEmpty())
            dialogConsumi->setObjectName(QString::fromUtf8("dialogConsumi"));
        dialogConsumi->resize(920, 779);
        buttonBox = new QDialogButtonBox(dialogConsumi);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(600, 730, 126, 25));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(dialogConsumi);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 901, 711));
        tabWidget->setIconSize(QSize(32, 16));
        tabConsumi = new QWidget();
        tabConsumi->setObjectName(QString::fromUtf8("tabConsumi"));
        tabConsumi->setMinimumSize(QSize(0, 440));
        groupBox = new QGroupBox(tabConsumi);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 881, 181));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(170, 20, 56, 21));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 150, 28));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        annuiDSpin = new QDoubleSpinBox(layoutWidget);
        annuiDSpin->setObjectName(QString::fromUtf8("annuiDSpin"));
        annuiDSpin->setDecimals(3);
        annuiDSpin->setMaximum(1e+06);
        annuiDSpin->setSingleStep(2);

        horizontalLayout->addWidget(annuiDSpin);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(11, 51, 41, 16));
        tableMonthly = new QTableWidget(groupBox);
        if (tableMonthly->columnCount() < 13)
            tableMonthly->setColumnCount(13);
        if (tableMonthly->rowCount() < 2)
            tableMonthly->setRowCount(2);
        tableMonthly->setObjectName(QString::fromUtf8("tableMonthly"));
        tableMonthly->setGeometry(QRect(186, 51, 681, 101));
        tableMonthly->setFrameShape(QFrame::Box);
        tableMonthly->setFrameShadow(QFrame::Raised);
        tableMonthly->setLineWidth(1);
        tableMonthly->setMidLineWidth(1);
        tableMonthly->setRowCount(2);
        tableMonthly->setColumnCount(13);
        comboMonthly = new QComboBox(groupBox);
        comboMonthly->setObjectName(QString::fromUtf8("comboMonthly"));
        comboMonthly->setGeometry(QRect(60, 50, 111, 25));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 90, 151, 41));
        label_6->setAutoFillBackground(false);
        label_6->setWordWrap(true);
        labelWarning = new QLabel(groupBox);
        labelWarning->setObjectName(QString::fromUtf8("labelWarning"));
        labelWarning->setGeometry(QRect(20, 90, 141, 71));
        labelWarning->setWordWrap(true);
        label_3 = new QLabel(tabConsumi);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 210, 72, 16));
        tableHourly = new QTableWidget(tabConsumi);
        if (tableHourly->columnCount() < 2)
            tableHourly->setColumnCount(2);
        if (tableHourly->rowCount() < 24)
            tableHourly->setRowCount(24);
        tableHourly->setObjectName(QString::fromUtf8("tableHourly"));
        tableHourly->setGeometry(QRect(20, 280, 181, 331));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableHourly->sizePolicy().hasHeightForWidth());
        tableHourly->setSizePolicy(sizePolicy);
        tableHourly->setRowCount(24);
        tableHourly->setColumnCount(2);
        tableHourly->horizontalHeader()->setMinimumSectionSize(8);
        plotHourly = new QwtPlot(tabConsumi);
        plotHourly->setObjectName(QString::fromUtf8("plotHourly"));
        plotHourly->setGeometry(QRect(240, 250, 641, 331));
        comboHourly = new QComboBox(tabConsumi);
        comboHourly->setObjectName(QString::fromUtf8("comboHourly"));
        comboHourly->setGeometry(QRect(100, 210, 111, 25));
        label_5 = new QLabel(tabConsumi);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 620, 81, 16));
        labelTotal = new QLabel(tabConsumi);
        labelTotal->setObjectName(QString::fromUtf8("labelTotal"));
        labelTotal->setGeometry(QRect(120, 620, 81, 16));
        labelTotal->setFrameShape(QFrame::Panel);
        labelWarningHours = new QLabel(tabConsumi);
        labelWarningHours->setObjectName(QString::fromUtf8("labelWarningHours"));
        labelWarningHours->setGeometry(QRect(20, 250, 181, 31));
        labelWarningHours->setWordWrap(true);
        labelTotalPercent = new QLabel(tabConsumi);
        labelTotalPercent->setObjectName(QString::fromUtf8("labelTotalPercent"));
        labelTotalPercent->setGeometry(QRect(120, 640, 81, 16));
        labelTotalPercent->setFrameShape(QFrame::Panel);
        tabWidget->addTab(tabConsumi, QString());
        buttonSave = new QPushButton(dialogConsumi);
        buttonSave->setObjectName(QString::fromUtf8("buttonSave"));
        buttonSave->setGeometry(QRect(740, 730, 71, 25));
        buttonCarica = new QPushButton(dialogConsumi);
        buttonCarica->setObjectName(QString::fromUtf8("buttonCarica"));
        buttonCarica->setGeometry(QRect(820, 730, 84, 25));
        buttonCarica->setStyleSheet(QString::fromUtf8(""));

        retranslateUi(dialogConsumi);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialogConsumi, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialogConsumi, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(dialogConsumi);
    } // setupUi

    void retranslateUi(QDialog *dialogConsumi)
    {
        dialogConsumi->setWindowTitle(QApplication::translate("dialogConsumi", "Consumi Elettrici", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("dialogConsumi", "Consumi medi", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("dialogConsumi", "kWh", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dialogConsumi", "Annui", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("dialogConsumi", "Mensili", 0, QApplication::UnicodeUTF8));
        comboMonthly->clear();
        comboMonthly->insertItems(0, QStringList()
         << QApplication::translate("dialogConsumi", "Uniformi", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dialogConsumi", "Stagionali/Estate", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dialogConsumi", "Stagionali/Inverno", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dialogConsumi", "Custom", 0, QApplication::UnicodeUTF8)
        );
        label_6->setText(QString());
        labelWarning->setText(QString());
        label_3->setText(QApplication::translate("dialogConsumi", "Carichi orari", 0, QApplication::UnicodeUTF8));
        comboHourly->clear();
        comboHourly->insertItems(0, QStringList()
         << QApplication::translate("dialogConsumi", "Uniformi", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dialogConsumi", "Tipico", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dialogConsumi", "Custom", 0, QApplication::UnicodeUTF8)
        );
        label_5->setText(QApplication::translate("dialogConsumi", "Totale (kWh)", 0, QApplication::UnicodeUTF8));
        labelTotal->setText(QApplication::translate("dialogConsumi", "0", 0, QApplication::UnicodeUTF8));
        labelWarningHours->setText(QString());
        labelTotalPercent->setText(QApplication::translate("dialogConsumi", "0", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabConsumi), QApplication::translate("dialogConsumi", "Consumi orari", 0, QApplication::UnicodeUTF8));
        buttonSave->setText(QApplication::translate("dialogConsumi", "Salva", 0, QApplication::UnicodeUTF8));
        buttonCarica->setText(QApplication::translate("dialogConsumi", "Carica", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(dialogConsumi);
    } // retranslateUi

};

namespace Ui {
    class dialogConsumi: public Ui_dialogConsumi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CONSUMI_H
