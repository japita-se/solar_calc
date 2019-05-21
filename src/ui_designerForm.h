/********************************************************************************
** Form generated from reading UI file 'designerForm.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESIGNERFORM_H
#define UI_DESIGNERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_formDesigner
{
public:
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *label_3;
    QLineEdit *lineTitle;
    QLabel *label_4;
    QDateEdit *dateEdit;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineName;
    QLabel *label_2;
    QLineEdit *lineCompany;
    QLabel *label_10;
    QLineEdit *lineLogo;
    QPushButton *pushLogo;
    QLabel *labelLogo;
    QLabel *label_8;
    QLineEdit *lineAlbo;
    QLabel *label_7;
    QLineEdit *lineReviewer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLineEdit *lineClient;
    QLabel *label_6;
    QLineEdit *lineClientAddress;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QTextEdit *textNotes;

    void setupUi(QWidget *formDesigner)
    {
        if (formDesigner->objectName().isEmpty())
            formDesigner->setObjectName(QString::fromUtf8("formDesigner"));
        formDesigner->resize(484, 511);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/users.png"), QSize(), QIcon::Normal, QIcon::Off);
        formDesigner->setWindowIcon(icon);
        gridLayout_5 = new QGridLayout(formDesigner);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_3 = new QLabel(formDesigner);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 0, 0, 1, 1);

        lineTitle = new QLineEdit(formDesigner);
        lineTitle->setObjectName(QString::fromUtf8("lineTitle"));

        gridLayout_4->addWidget(lineTitle, 0, 1, 1, 1);

        label_4 = new QLabel(formDesigner);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        dateEdit = new QDateEdit(formDesigner);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));

        gridLayout_4->addWidget(dateEdit, 1, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 0, 1, 1);

        groupBox = new QGroupBox(formDesigner);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineName = new QLineEdit(groupBox);
        lineName->setObjectName(QString::fromUtf8("lineName"));

        gridLayout->addWidget(lineName, 0, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineCompany = new QLineEdit(groupBox);
        lineCompany->setObjectName(QString::fromUtf8("lineCompany"));

        gridLayout->addWidget(lineCompany, 1, 1, 1, 2);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 2, 0, 1, 1);

        lineLogo = new QLineEdit(groupBox);
        lineLogo->setObjectName(QString::fromUtf8("lineLogo"));

        gridLayout->addWidget(lineLogo, 2, 1, 1, 1);

        pushLogo = new QPushButton(groupBox);
        pushLogo->setObjectName(QString::fromUtf8("pushLogo"));

        gridLayout->addWidget(pushLogo, 2, 2, 1, 1);

        labelLogo = new QLabel(groupBox);
        labelLogo->setObjectName(QString::fromUtf8("labelLogo"));
        labelLogo->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(labelLogo, 3, 1, 1, 2);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 4, 0, 1, 1);

        lineAlbo = new QLineEdit(groupBox);
        lineAlbo->setObjectName(QString::fromUtf8("lineAlbo"));

        gridLayout->addWidget(lineAlbo, 4, 1, 1, 2);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        lineReviewer = new QLineEdit(groupBox);
        lineReviewer->setObjectName(QString::fromUtf8("lineReviewer"));

        gridLayout->addWidget(lineReviewer, 5, 1, 1, 2);


        gridLayout_5->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(formDesigner);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        lineClient = new QLineEdit(groupBox_2);
        lineClient->setObjectName(QString::fromUtf8("lineClient"));

        gridLayout_2->addWidget(lineClient, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        lineClientAddress = new QLineEdit(groupBox_2);
        lineClientAddress->setObjectName(QString::fromUtf8("lineClientAddress"));

        gridLayout_2->addWidget(lineClientAddress, 1, 1, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_3 = new QGroupBox(formDesigner);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        textNotes = new QTextEdit(groupBox_3);
        textNotes->setObjectName(QString::fromUtf8("textNotes"));

        gridLayout_3->addWidget(textNotes, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 3, 0, 1, 1);


        retranslateUi(formDesigner);

        QMetaObject::connectSlotsByName(formDesigner);
    } // setupUi

    void retranslateUi(QWidget *formDesigner)
    {
        formDesigner->setWindowTitle(QApplication::translate("formDesigner", "Dettagli progetto", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("formDesigner", "Titolo progetto", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("formDesigner", "Data", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("formDesigner", "Progettista", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("formDesigner", "Nome e cognome", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("formDesigner", "Azienda", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("formDesigner", "Logo", 0, QApplication::UnicodeUTF8));
        pushLogo->setText(QApplication::translate("formDesigner", "...", 0, QApplication::UnicodeUTF8));
        labelLogo->setText(QString());
        label_8->setText(QApplication::translate("formDesigner", "N. Albo", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("formDesigner", "Revisore", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("formDesigner", "Cliente", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("formDesigner", "Nome o sigla", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("formDesigner", "Indirizzo", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("formDesigner", "Note frontespizio", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class formDesigner: public Ui_formDesigner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESIGNERFORM_H
