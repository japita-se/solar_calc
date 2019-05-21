/********************************************************************************
** Form generated from reading UI file 'proprieta.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPRIETA_H
#define UI_PROPRIETA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Proprieta
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabProprieta;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QSpinBox *sNumOfDecimals;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QComboBox *comboLang;
    QLabel *label_2;
    QWidget *tab_2;
    QGridLayout *gridLayout_5;
    QCheckBox *checkProxy;
    QGroupBox *groupProxy;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLineEdit *lineHost;
    QLabel *label_4;
    QLineEdit *lineUser;
    QLabel *label_5;
    QLineEdit *linePass;
    QLabel *label_7;
    QSpinBox *spinPorta;
    QLabel *label_6;
    QComboBox *comboType;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Proprieta)
    {
        if (Proprieta->objectName().isEmpty())
            Proprieta->setObjectName(QString::fromUtf8("Proprieta"));
        Proprieta->resize(486, 429);
        QIcon icon;
        icon.addFile(QString::fromUtf8("app.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Proprieta->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(Proprieta);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabProprieta = new QTabWidget(Proprieta);
        tabProprieta->setObjectName(QString::fromUtf8("tabProprieta"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        sNumOfDecimals = new QSpinBox(groupBox);
        sNumOfDecimals->setObjectName(QString::fromUtf8("sNumOfDecimals"));
        sNumOfDecimals->setMaximum(8);

        gridLayout->addWidget(sNumOfDecimals, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboLang = new QComboBox(groupBox_2);
        comboLang->setObjectName(QString::fromUtf8("comboLang"));

        gridLayout_2->addWidget(comboLang, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setPointSize(14);
        label_2->setFont(font);
        label_2->setWordWrap(true);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 1, 0, 1, 1);

        tabProprieta->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_5 = new QGridLayout(tab_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        checkProxy = new QCheckBox(tab_2);
        checkProxy->setObjectName(QString::fromUtf8("checkProxy"));

        gridLayout_5->addWidget(checkProxy, 0, 0, 1, 1);

        groupProxy = new QGroupBox(tab_2);
        groupProxy->setObjectName(QString::fromUtf8("groupProxy"));
        groupProxy->setMaximumSize(QSize(300, 16777215));
        gridLayout_4 = new QGridLayout(groupProxy);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label = new QLabel(groupProxy);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        lineHost = new QLineEdit(groupProxy);
        lineHost->setObjectName(QString::fromUtf8("lineHost"));
        lineHost->setMaximumSize(QSize(100, 16777215));

        gridLayout_4->addWidget(lineHost, 0, 1, 1, 1);

        label_4 = new QLabel(groupProxy);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        lineUser = new QLineEdit(groupProxy);
        lineUser->setObjectName(QString::fromUtf8("lineUser"));
        lineUser->setMaximumSize(QSize(100, 16777215));

        gridLayout_4->addWidget(lineUser, 1, 1, 1, 1);

        label_5 = new QLabel(groupProxy);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 2, 0, 1, 1);

        linePass = new QLineEdit(groupProxy);
        linePass->setObjectName(QString::fromUtf8("linePass"));
        linePass->setMaximumSize(QSize(100, 16777215));

        gridLayout_4->addWidget(linePass, 2, 1, 1, 1);

        label_7 = new QLabel(groupProxy);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 3, 0, 1, 1);

        spinPorta = new QSpinBox(groupProxy);
        spinPorta->setObjectName(QString::fromUtf8("spinPorta"));
        spinPorta->setMaximumSize(QSize(100, 16777215));
        spinPorta->setMaximum(65000);
        spinPorta->setValue(1080);

        gridLayout_4->addWidget(spinPorta, 3, 1, 1, 1);

        label_6 = new QLabel(groupProxy);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 4, 0, 1, 1);

        comboType = new QComboBox(groupProxy);
        comboType->setObjectName(QString::fromUtf8("comboType"));

        gridLayout_4->addWidget(comboType, 4, 1, 1, 1);


        gridLayout_5->addWidget(groupProxy, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(216, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 1, 1, 1);

        tabProprieta->addTab(tab_2, QString());

        verticalLayout->addWidget(tabProprieta);

        buttonBox = new QDialogButtonBox(Proprieta);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Proprieta);
        QObject::connect(buttonBox, SIGNAL(accepted()), Proprieta, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Proprieta, SLOT(reject()));

        tabProprieta->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Proprieta);
    } // setupUi

    void retranslateUi(QDialog *Proprieta)
    {
        Proprieta->setWindowTitle(QApplication::translate("Proprieta", "Opzioni", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Proprieta", "Risultati economici", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Proprieta", "Numero decimali", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Proprieta", "Lingua", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Proprieta", "Riavviare l'applicazione se la lingua cambia", 0, QApplication::UnicodeUTF8));
        tabProprieta->setTabText(tabProprieta->indexOf(tab), QApplication::translate("Proprieta", "Generale", 0, QApplication::UnicodeUTF8));
        checkProxy->setText(QApplication::translate("Proprieta", "Abilita proxy", 0, QApplication::UnicodeUTF8));
        groupProxy->setTitle(QApplication::translate("Proprieta", "Parametri", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Proprieta", "Host", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Proprieta", "Username", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Proprieta", "Password", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Proprieta", "Porta", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Proprieta", "Tipo Proxy", 0, QApplication::UnicodeUTF8));
        comboType->clear();
        comboType->insertItems(0, QStringList()
         << QApplication::translate("Proprieta", "DefaultProxy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Proprieta", "Socks5Proxy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Proprieta", "HttpProxy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Proprieta", "HttpCachingProxy", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Proprieta", "FtpCachingProxy", 0, QApplication::UnicodeUTF8)
        );
        tabProprieta->setTabText(tabProprieta->indexOf(tab_2), QApplication::translate("Proprieta", "Connessione", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Proprieta: public Ui_Proprieta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPRIETA_H
