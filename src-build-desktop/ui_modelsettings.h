/********************************************************************************
** Form generated from reading UI file 'modelsettings.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELSETTINGS_H
#define UI_MODELSETTINGS_H

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
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelSettings
{
public:
    QGridLayout *gridLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QRadioButton *radioUNI;
    QRadioButton *radioEnea;
    QRadioButton *radioErbs;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_3;
    QGridLayout *gridLayout_2;
    QRadioButton *radioNOCT1;
    QRadioButton *radioCEA;
    QRadioButton *radioOther;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_4;
    QGridLayout *gridLayout;
    QComboBox *comboType;
    QLabel *labelType;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QGridLayout *gridLayout_4;
    QRadioButton *radioOmbreLineari;
    QRadioButton *radioOmbreSpline;
    QSpacerItem *verticalSpacer_4;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ModelSettings)
    {
        if (ModelSettings->objectName().isEmpty())
            ModelSettings->setObjectName(QString::fromUtf8("ModelSettings"));
        ModelSettings->resize(488, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icona.png"), QSize(), QIcon::Normal, QIcon::Off);
        ModelSettings->setWindowIcon(icon);
        gridLayout_5 = new QGridLayout(ModelSettings);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tabWidget = new QTabWidget(ModelSettings);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        radioUNI = new QRadioButton(tab);
        radioUNI->setObjectName(QString::fromUtf8("radioUNI"));

        gridLayout_3->addWidget(radioUNI, 0, 0, 1, 1);

        radioEnea = new QRadioButton(tab);
        radioEnea->setObjectName(QString::fromUtf8("radioEnea"));
        radioEnea->setChecked(true);

        gridLayout_3->addWidget(radioEnea, 1, 0, 1, 1);

        radioErbs = new QRadioButton(tab);
        radioErbs->setObjectName(QString::fromUtf8("radioErbs"));

        gridLayout_3->addWidget(radioErbs, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 234, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 3, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_2 = new QGridLayout(tab_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioNOCT1 = new QRadioButton(tab_3);
        radioNOCT1->setObjectName(QString::fromUtf8("radioNOCT1"));
        radioNOCT1->setChecked(true);

        gridLayout_2->addWidget(radioNOCT1, 0, 0, 1, 1);

        radioCEA = new QRadioButton(tab_3);
        radioCEA->setObjectName(QString::fromUtf8("radioCEA"));

        gridLayout_2->addWidget(radioCEA, 1, 0, 1, 1);

        radioOther = new QRadioButton(tab_3);
        radioOther->setObjectName(QString::fromUtf8("radioOther"));

        gridLayout_2->addWidget(radioOther, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 263, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 3, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout = new QGridLayout(tab_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboType = new QComboBox(tab_4);
        comboType->setObjectName(QString::fromUtf8("comboType"));

        gridLayout->addWidget(comboType, 0, 0, 1, 1);

        labelType = new QLabel(tab_4);
        labelType->setObjectName(QString::fromUtf8("labelType"));

        gridLayout->addWidget(labelType, 0, 1, 2, 1);

        verticalSpacer = new QSpacerItem(20, 263, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_4 = new QGridLayout(tab_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        radioOmbreLineari = new QRadioButton(tab_2);
        radioOmbreLineari->setObjectName(QString::fromUtf8("radioOmbreLineari"));

        gridLayout_4->addWidget(radioOmbreLineari, 0, 0, 1, 1);

        radioOmbreSpline = new QRadioButton(tab_2);
        radioOmbreSpline->setObjectName(QString::fromUtf8("radioOmbreSpline"));

        gridLayout_4->addWidget(radioOmbreSpline, 1, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 263, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_4, 2, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());

        gridLayout_5->addWidget(tabWidget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(ModelSettings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_5->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(ModelSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), ModelSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ModelSettings, SLOT(reject()));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ModelSettings);
    } // setupUi

    void retranslateUi(QDialog *ModelSettings)
    {
        ModelSettings->setWindowTitle(QApplication::translate("ModelSettings", "Impostazioni generali", 0, QApplication::UnicodeUTF8));
        radioUNI->setText(QApplication::translate("ModelSettings", "modello UNI", 0, QApplication::UnicodeUTF8));
        radioEnea->setText(QApplication::translate("ModelSettings", "modello ENEA", 0, QApplication::UnicodeUTF8));
        radioErbs->setText(QApplication::translate("ModelSettings", "Erbs81", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ModelSettings", "Correlazione diretta/diffusa", 0, QApplication::UnicodeUTF8));
        radioNOCT1->setText(QApplication::translate("ModelSettings", " Standard, NOCT+wind (Duffy & Beckaman 2006)", 0, QApplication::UnicodeUTF8));
        radioCEA->setText(QApplication::translate("ModelSettings", " CEA, noNOCT + wind, 2004", 0, QApplication::UnicodeUTF8));
        radioOther->setText(QApplication::translate("ModelSettings", "other, MATTEI 2005", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("ModelSettings", "Perdite termiche", 0, QApplication::UnicodeUTF8));
        comboType->clear();
        comboType->insertItems(0, QStringList()
         << QApplication::translate("ModelSettings", "Tilt fisso/ Singola falda e/o array", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModelSettings", "Inseguitore biassiale", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ModelSettings", "Doppia falda", 0, QApplication::UnicodeUTF8)
        );
        labelType->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("ModelSettings", "Tipo sistema", 0, QApplication::UnicodeUTF8));
        radioOmbreLineari->setText(QApplication::translate("ModelSettings", "interpolazione lineare", 0, QApplication::UnicodeUTF8));
        radioOmbreSpline->setText(QApplication::translate("ModelSettings", "interpolazione spline", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ModelSettings", "Unione ombre", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ModelSettings: public Ui_ModelSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELSETTINGS_H
