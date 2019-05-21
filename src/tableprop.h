#ifndef TABLEPROP_H
#define TABLEPROP_H

#include <QDialog>
#include "ui_tableprop.h"



class tableprop : public QDialog, public Ui::tableprop
{
    Q_OBJECT

public:
    explicit tableprop(QWidget *parent = 0);
    ~tableprop();

private:
    Ui::tableprop *ui;
    int row,col,border,align,width,cellspacing,cellpadding;
    bool donotupdate;
public:
    void setRows(int r);
    void setBorder(int t);
    void setCols(int c);
    int getAlign();
    int getWidth();
    int getRows();
    int getCols();
    int getBorder();
    int getCellspacing();
    int getCellpadding();
private slots:
    void updateRow(int a);
    void updateCol(int a);
    void updateBorder(int a);
    void updateAlign(int a);
    void updateWidth(int a);
    void updateCellSpacing(int a);
    void updateCellPadding(int a);
};

#endif // TABLEPROP_H
