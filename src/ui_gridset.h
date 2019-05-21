/********************************************************************************
** Form generated from reading UI file 'gridset.ui'
**
** Created: Sat 6. Apr 22:42:46 2013
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRIDSET_H
#define UI_GRIDSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GridSet
{
public:
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QCheckBox *checkAsseX;
    QCheckBox *checkAsseY;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GridSet)
    {
        if (GridSet->objectName().isEmpty())
            GridSet->setObjectName(QString::fromUtf8("GridSet"));
        GridSet->resize(200, 110);
        widget = new QWidget(GridSet);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 10, 162, 86));
        vboxLayout = new QVBoxLayout(widget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(0, 0, 0, 0);
        checkAsseX = new QCheckBox(widget);
        checkAsseX->setObjectName(QString::fromUtf8("checkAsseX"));

        vboxLayout->addWidget(checkAsseX);

        checkAsseY = new QCheckBox(widget);
        checkAsseY->setObjectName(QString::fromUtf8("checkAsseY"));

        vboxLayout->addWidget(checkAsseY);

        buttonBox = new QDialogButtonBox(widget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(GridSet);
        QObject::connect(buttonBox, SIGNAL(accepted()), GridSet, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GridSet, SLOT(reject()));

        QMetaObject::connectSlotsByName(GridSet);
    } // setupUi

    void retranslateUi(QDialog *GridSet)
    {
        GridSet->setWindowTitle(QApplication::translate("GridSet", "Griglia", 0, QApplication::UnicodeUTF8));
        checkAsseX->setText(QApplication::translate("GridSet", "Asse X", 0, QApplication::UnicodeUTF8));
        checkAsseY->setText(QApplication::translate("GridSet", "Asse Y", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GridSet: public Ui_GridSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRIDSET_H
