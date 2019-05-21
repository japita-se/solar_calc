/********************************************************************************
** Form generated from reading UI file 'info.ui'
**
** Created: Mon 25. Oct 20:49:54 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_H
#define UI_INFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogInfo
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogInfo)
    {
        if (DialogInfo->objectName().isEmpty())
            DialogInfo->setObjectName(QString::fromUtf8("DialogInfo"));
        DialogInfo->resize(400, 300);
        gridLayout = new QGridLayout(DialogInfo);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEdit = new QTextEdit(DialogInfo);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout->addWidget(textEdit, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogInfo);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(DialogInfo);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogInfo, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogInfo, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogInfo);
    } // setupUi

    void retranslateUi(QDialog *DialogInfo)
    {
        DialogInfo->setWindowTitle(QApplication::translate("DialogInfo", "Informazioni", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DialogInfo: public Ui_DialogInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_H
