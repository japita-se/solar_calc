#ifndef DATIPANNELLO_H
#define DATIPANNELLO_H
#include "ui_datipannello.h"
#include <QSqlDatabase>
#include <QDialog>
#include <QModelIndex>
#include "data.h"
class QSqlRecord;
class QSqlTableModel;
class QStringListModel;
class QTableView;
class QSortFilterProxyModel;
class QAction;
class MyFilterProxyModel;
class DatiPannello: public QDialog, public Ui::DatiPannello
{
	Q_OBJECT
public:
	DatiPannello(QWidget* parent=0);
	~DatiPannello();
	void setDatabase(const QSqlDatabase &dbname,const QString &table);
	void refreshView();
	panel getSelectedPanel(int row);
public slots:
	panel getSelectedPanel();
	
private:
        QSqlTableModel   *model;
        QStringListModel *listModel;
         QSortFilterProxyModel *proxyListModel;
        MyFilterProxyModel         *proxyModel;
	QSqlDatabase database;
	QString table;
	 
private slots:
        void deleteMarca();
        void setupActions();
        void popUpMenu(const QPoint &a);
	void submitChange();
	void enableApply(const QModelIndex &i);
	void deleteRow();
	void initializeModel();
        
	void getPanel();
	void beforeUpdate(int i );
	void setFilter(const QString &s);
        void setFilter(const QModelIndex &s);
	 
private:
	panel out;
        QAction* a_delete;
        QModelIndex currentIndex;
        QStringList modelsPV;
        QString sourceString;
        //int currentIndex ;
	 
};
#endif
