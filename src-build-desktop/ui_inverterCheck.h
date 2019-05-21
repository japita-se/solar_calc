/********************************************************************************
** Form generated from reading UI file 'inverterCheck.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVERTERCHECK_H
#define UI_INVERTERCHECK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_inverterCheck
{
public:
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_4;
    QLabel *label_2;
    QLineEdit *lineCampi;
    QLabel *label_4;
    QLineEdit *linePannelli;
    QGridLayout *gridLayout;
    QPushButton *pushSuggerisci;
    QPushButton *pushElimina;
    QPushButton *pushCheck;
    QPushButton *pushScegli;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *textEdit;
    QGridLayout *gridLayout_5;
    QLabel *label_10;
    QComboBox *comboCampi;
    QLabel *label_11;
    QComboBox *comboInverter;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *inverterCheck)
    {
        if (inverterCheck->objectName().isEmpty())
            inverterCheck->setObjectName(QString::fromUtf8("inverterCheck"));
        inverterCheck->resize(813, 725);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(inverterCheck->sizePolicy().hasHeightForWidth());
        inverterCheck->setSizePolicy(sizePolicy);
        inverterCheck->setMaximumSize(QSize(1677, 1677));
        gridLayout_3 = new QGridLayout(inverterCheck);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new QWidget(inverterCheck);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_3->addWidget(widget, 1, 0, 2, 2);

        verticalSpacer = new QSpacerItem(20, 351, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 1, 1, 1);

        groupBox = new QGroupBox(inverterCheck);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{ border: 2px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex;  \n"
" }\n"
"QGroupBox::title { \n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
" \n"
"}"));
        gridLayout_6 = new QGridLayout(groupBox);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        lineCampi = new QLineEdit(groupBox);
        lineCampi->setObjectName(QString::fromUtf8("lineCampi"));

        gridLayout_4->addWidget(lineCampi, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        linePannelli = new QLineEdit(groupBox);
        linePannelli->setObjectName(QString::fromUtf8("linePannelli"));

        gridLayout_4->addWidget(linePannelli, 1, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushSuggerisci = new QPushButton(groupBox);
        pushSuggerisci->setObjectName(QString::fromUtf8("pushSuggerisci"));

        gridLayout->addWidget(pushSuggerisci, 0, 0, 1, 1);

        pushElimina = new QPushButton(groupBox);
        pushElimina->setObjectName(QString::fromUtf8("pushElimina"));

        gridLayout->addWidget(pushElimina, 1, 0, 1, 1);

        pushCheck = new QPushButton(groupBox);
        pushCheck->setObjectName(QString::fromUtf8("pushCheck"));

        gridLayout->addWidget(pushCheck, 2, 0, 1, 1);

        pushScegli = new QPushButton(groupBox);
        pushScegli->setObjectName(QString::fromUtf8("pushScegli"));

        gridLayout->addWidget(pushScegli, 3, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout, 0, 1, 2, 1);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox\n"
"{ border: 2px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 2ex;  \n"
" }\n"
"QGroupBox::title { \n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left; /* position at the top center */\n"
"     padding: 0 3px;\n"
" \n"
"}"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(225, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        textEdit = new QTextEdit(groupBox_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_2->addWidget(textEdit, 1, 0, 1, 2);


        gridLayout_6->addWidget(groupBox_2, 0, 2, 3, 1);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_10->setFont(font);

        gridLayout_5->addWidget(label_10, 0, 0, 1, 1);

        comboCampi = new QComboBox(groupBox);
        comboCampi->setObjectName(QString::fromUtf8("comboCampi"));

        gridLayout_5->addWidget(comboCampi, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);

        gridLayout_5->addWidget(label_11, 1, 0, 1, 1);

        comboInverter = new QComboBox(groupBox);
        comboInverter->setObjectName(QString::fromUtf8("comboInverter"));

        gridLayout_5->addWidget(comboInverter, 1, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 1, 0, 1, 1);

        treeWidget = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->header()->setVisible(true);

        gridLayout_6->addWidget(treeWidget, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 2);


        retranslateUi(inverterCheck);

        QMetaObject::connectSlotsByName(inverterCheck);
    } // setupUi

    void retranslateUi(QWidget *inverterCheck)
    {
        inverterCheck->setWindowTitle(QApplication::translate("inverterCheck", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("inverterCheck", "Sistema", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("inverterCheck", "Campi (C)", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("inverterCheck", "Pannelli/Stringa (S)", 0, QApplication::UnicodeUTF8));
        pushSuggerisci->setText(QApplication::translate("inverterCheck", "Suggerisci", 0, QApplication::UnicodeUTF8));
        pushElimina->setText(QApplication::translate("inverterCheck", "Elimina", 0, QApplication::UnicodeUTF8));
        pushCheck->setText(QApplication::translate("inverterCheck", "Check", 0, QApplication::UnicodeUTF8));
        pushScegli->setText(QApplication::translate("inverterCheck", "Scegli", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("inverterCheck", " Rapporto", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("inverterCheck", "Campo num.", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("inverterCheck", "Modello", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class inverterCheck: public Ui_inverterCheck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVERTERCHECK_H
