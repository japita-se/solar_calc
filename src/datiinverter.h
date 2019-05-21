#ifndef DATIINVERTER_H
#define DATIINVERTER_H
#include "ui_datiinverter.h"
#include <QSqlDatabase>
#include <QDialog>
#include <QModelIndex>
#include "data.h"
class QSqlRecord;
class QSqlTableModel;
class QTableView;
class QSortFilterProxyModel;
class QAction;
class MyFilterProxyModel;
class DatiInverter: public QDialog, public Ui::DatiInverter
{
	Q_OBJECT
public:
	DatiInverter(QWidget* parent=0);
	~DatiInverter();
	void setDatabase(const QSqlDatabase &dbname,const QString &table);
	void refreshView();
	inverter getSelectedInverter(int i);
public slots:
	inverter getSelectedInverter();
	
private:
	QSqlTableModel *model;
        QStringListModel *listModel;
        QSortFilterProxyModel *proxyListModel;
        MyFilterProxyModel         *proxyModel;

	QSqlDatabase database;
	QString table;
	QTableView *tableView;
private slots:
        void deleteMarca();
        void setupActions();
        void popUpMenu(const QPoint &a);
	void submitChange();
	void enableApply(const QModelIndex &i);
	void deleteRow();
	 
	void initializeModel();
	void getInverter();
 	void beforeUpdate(int i, QSqlRecord &r);
	void setFilter(const QString &s);
        void setFilter(const QModelIndex &a);
	 
private:
	inverter inv;
        QAction* a_delete;
        QModelIndex currentIndex;
        QStringList modelsInv;
        QString sourceString;
};
#endif
