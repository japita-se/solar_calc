/********************************************************************************
** Form generated from reading UI file 'simecooptions.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMECOOPTIONS_H
#define UI_SIMECOOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_dialogSimOptions
{
public:
    QGridLayout *gridLayout_2;
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QLabel *label;
    QRadioButton *radioNettoMean;
    QRadioButton *radioBonusOnly;
    QSpacerItem *verticalSpacer_2;
    QRadioButton *radioRIBCS;

    void setupUi(QDialog *dialogSimOptions)
    {
        if (dialogSimOptions->objectName().isEmpty())
            dialogSimOptions->setObjectName(QString::fromUtf8("dialogSimOptions"));
        dialogSimOptions->resize(400, 300);
        dialogSimOptions->setMaximumSize(QSize(400, 300));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/play2.png"), QSize(), QIcon::Normal, QIcon::Off);
        dialogSimOptions->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(dialogSimOptions);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        buttonBox = new QDialogButtonBox(dialogSimOptions);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 0, 1, 1);

        tabWidget = new QTabWidget(dialogSimOptions);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        radioNettoMean = new QRadioButton(tab);
        radioNettoMean->setObjectName(QString::fromUtf8("radioNettoMean"));
        radioNettoMean->setChecked(true);

        gridLayout->addWidget(radioNettoMean, 1, 0, 1, 1);

        radioBonusOnly = new QRadioButton(tab);
        radioBonusOnly->setObjectName(QString::fromUtf8("radioBonusOnly"));
        radioBonusOnly->setChecked(false);

        gridLayout->addWidget(radioBonusOnly, 3, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(238, 17, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 4, 0, 1, 1);

        radioRIBCS = new QRadioButton(tab);
        radioRIBCS->setObjectName(QString::fromUtf8("radioRIBCS"));

        gridLayout->addWidget(radioRIBCS, 2, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(dialogSimOptions);
        QObject::connect(buttonBox, SIGNAL(accepted()), dialogSimOptions, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), dialogSimOptions, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(dialogSimOptions);
    } // setupUi

    void retranslateUi(QDialog *dialogSimOptions)
    {
        dialogSimOptions->setWindowTitle(QApplication::translate("dialogSimOptions", "Opzioni di simulazione economica", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dialogSimOptions", "Nel calcolo degli anni di finanziamento suggeriti usa per la rata annuale  il valore medio di:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioNettoMean->setToolTip(QApplication::translate("dialogSimOptions", "<p> Ricavi sono per Conto Scambio, o per Vendita, e RIB </p>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioNettoMean->setText(QApplication::translate("dialogSimOptions", "MOL- TasseSgravi ", 0, QApplication::UnicodeUTF8));
        radioBonusOnly->setText(QApplication::translate("dialogSimOptions", "Incentivi - Tasse&Sgravi - Costi ", 0, QApplication::UnicodeUTF8));
        radioRIBCS->setText(QApplication::translate("dialogSimOptions", "MOL -TasseSgravi - RIB - CS", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("dialogSimOptions", "Algoritmi", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dialogSimOptions: public Ui_dialogSimOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMECOOPTIONS_H
