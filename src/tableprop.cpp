#include "tableprop.h"
#include <QDebug>


tableprop::tableprop(QWidget *parent) :    QDialog(parent)

{
    setupUi(this);
        col = 1;
        row = 1;
        width =100;
        align = 0;
        border = 1;
        cellspacing = 0;
        cellpadding = 0;
    connect(spinRow,SIGNAL(valueChanged(int)),SLOT(updateRow(int)));
    connect(spinCol,SIGNAL(valueChanged(int)),SLOT(updateCol(int)));
    connect(spinBorder,SIGNAL(valueChanged(int)),SLOT(updateBorder(int)));
    connect(spinWidth,SIGNAL(valueChanged(int)),SLOT(updateWidth(int)));
    connect(comboAlign,SIGNAL(currentIndexChanged(int)),SLOT(updateAlign(int)));
    connect(spinCellSpacing,SIGNAL(valueChanged(int)),SLOT(updateCellSpacing(int)));
    connect(spinCellPadding,SIGNAL(valueChanged(int)),SLOT(updateCellPadding(int)));
    donotupdate = false;

}
void tableprop::setBorder(int t)
{
    border = t;
}
void tableprop::updateRow(int a)
{
    if (!donotupdate)
        row = a;
}

void tableprop::updateAlign(int a)
{
     if (!donotupdate)
        align = a;
}

void tableprop::updateWidth(int a)
{
     if (!donotupdate)
        width = a;
}

void tableprop::updateCol(int a)
{
    if (!donotupdate)
        col = a;
}
void tableprop::updateBorder(int a)
{
    if (!donotupdate)
        border = a;

}
void tableprop::updateCellSpacing(int i)
{
    if (!donotupdate)
    cellspacing = i;
}
void tableprop::updateCellPadding(int i)
{
    if (!donotupdate)
    cellpadding = i;
}

void tableprop::setRows(int r)
{
    donotupdate = true;
    row = r;
    donotupdate = false;
}
void tableprop::setCols(int c)
{
    col = c;
}
int tableprop::getWidth()
{
    return width;
}
int tableprop::getAlign()
{
    return align;
}

int tableprop::getBorder()
{
    return border;
}
int tableprop::getRows()
{
    return row;
}
int tableprop::getCols()
{
    return col;
}
int tableprop::getCellpadding()
{
    return cellpadding;
}
int tableprop::getCellspacing()
{
    return cellspacing;
}

tableprop::~tableprop()
{
    delete ui;
}
