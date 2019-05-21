/********************************************************************************
** Form generated from reading UI file 'datiradiazione.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATIRADIAZIONE_H
#define UI_DATIRADIAZIONE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_DatiRadiazione
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *radioEnea;
    QRadioButton *radioUNI;
    QRadioButton *radioNasa;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioCustom;
    QLineEdit *linePath;
    QPushButton *pushCarica;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QRadioButton *radioMJ;
    QRadioButton *radioKWh;
    QGroupBox *groupBox_3;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DatiRadiazione)
    {
        if (DatiRadiazione->objectName().isEmpty())
            DatiRadiazione->setObjectName(QString::fromUtf8("DatiRadiazione"));
        DatiRadiazione->resize(435, 452);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/app.png"), QSize(), QIcon::Normal, QIcon::Off);
        DatiRadiazione->setWindowIcon(icon);
        gridLayout_4 = new QGridLayout(DatiRadiazione);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(DatiRadiazione);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        radioEnea = new QRadioButton(groupBox);
        radioEnea->setObjectName(QString::fromUtf8("radioEnea"));
        radioEnea->setChecked(true);

        gridLayout->addWidget(radioEnea, 0, 0, 1, 1);

        radioUNI = new QRadioButton(groupBox);
        radioUNI->setObjectName(QString::fromUtf8("radioUNI"));

        gridLayout->addWidget(radioUNI, 1, 0, 1, 1);

        radioNasa = new QRadioButton(groupBox);
        radioNasa->setObjectName(QString::fromUtf8("radioNasa"));

        gridLayout->addWidget(radioNasa, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioCustom = new QRadioButton(groupBox);
        radioCustom->setObjectName(QString::fromUtf8("radioCustom"));

        horizontalLayout->addWidget(radioCustom);

        linePath = new QLineEdit(groupBox);
        linePath->setObjectName(QString::fromUtf8("linePath"));

        horizontalLayout->addWidget(linePath);

        pushCarica = new QPushButton(groupBox);
        pushCarica->setObjectName(QString::fromUtf8("pushCarica"));

        horizontalLayout->addWidget(pushCarica);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(DatiRadiazione);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        radioMJ = new QRadioButton(groupBox_2);
        radioMJ->setObjectName(QString::fromUtf8("radioMJ"));

        gridLayout_2->addWidget(radioMJ, 0, 0, 1, 1);

        radioKWh = new QRadioButton(groupBox_2);
        radioKWh->setObjectName(QString::fromUtf8("radioKWh"));

        gridLayout_2->addWidget(radioKWh, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(DatiRadiazione);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 0, 311, 101));
        label->setTextFormat(Qt::PlainText);
        label->setWordWrap(true);

        gridLayout_4->addWidget(groupBox_3, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DatiRadiazione);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_4->addWidget(buttonBox, 3, 0, 1, 1);


        retranslateUi(DatiRadiazione);
        QObject::connect(buttonBox, SIGNAL(accepted()), DatiRadiazione, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DatiRadiazione, SLOT(reject()));

        QMetaObject::connectSlotsByName(DatiRadiazione);
    } // setupUi

    void retranslateUi(QDialog *DatiRadiazione)
    {
        DatiRadiazione->setWindowTitle(QApplication::translate("DatiRadiazione", "Dati di Radiazione", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DatiRadiazione", "Sorgente - Radiazione globale orizz. al suolo", 0, QApplication::UnicodeUTF8));
        radioEnea->setText(QApplication::translate("DatiRadiazione", "Enea", 0, QApplication::UnicodeUTF8));
        radioUNI->setText(QApplication::translate("DatiRadiazione", "UNI 10349", 0, QApplication::UnicodeUTF8));
        radioNasa->setText(QApplication::translate("DatiRadiazione", "NASA", 0, QApplication::UnicodeUTF8));
        radioCustom->setText(QApplication::translate("DatiRadiazione", "Custom File", 0, QApplication::UnicodeUTF8));
        pushCarica->setText(QApplication::translate("DatiRadiazione", "...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("DatiRadiazione", "Caratteristiche dati Custom", 0, QApplication::UnicodeUTF8));
        radioMJ->setText(QApplication::translate("DatiRadiazione", "MJ/m2", 0, QApplication::UnicodeUTF8));
        radioKWh->setText(QApplication::translate("DatiRadiazione", "kWh/m2", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("DatiRadiazione", "NOTA", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DatiRadiazione", "I dati di radiazione si riferiscono alla radiazione misurata o stimata sul piano orizzontale. La radiazione diffusa \303\250 calcolata comunque con il modello UNI 8477 (diffusione isotropica).", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DatiRadiazione: public Ui_DatiRadiazione {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATIRADIAZIONE_H
