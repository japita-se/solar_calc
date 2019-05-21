#ifndef MAGICTABLE_H
#define MAGICTABLE_H
//
// C++ Interface: magictable
//
// Description: 
//
//
// Author: Giuseppe De Marco <demarco.giu@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "ui_magictable.h"
#include <QDialog>
class MagicTable : public QDialog, public Ui::MagicTable {

	Q_OBJECT
public:
	MagicTable(QWidget* parent=0);
        void setLosses(const QVector<double> &a);
	QVector<double> getLosses();
	bool isDirty();
	void makeDirty(bool i);

private slots:
	void clearSelected();
	void popUpMenu(const QPoint &a);
	void update(QTableWidgetItem* i);
	void uniformize();
	void clearTable();
	void setTable();
        void updateTable();
protected:
	QAction *a_copy,*a_clear;
	void createActions();
	
	QVector<double> losses,lossesUndo;
        bool dirty,doNotUpdate;
};
#endif

