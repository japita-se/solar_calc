#include "magictable.h"
#include "doubledelegate.h"
#include "mymath.h"
#include <QtGui>
MagicTable::MagicTable(QWidget* parent) : QDialog(parent) {

	setupUi(this);
	createActions();
	losses.fill(0,12);

	setTable();
	clearTable();
	QVector<int> d;
	d = MyMath::serie(0,13);
	
        dirty       = false;
        doNotUpdate = false;
	tableWidget->setItemDelegate(new DoubleDelegate(d,1,0,2));
	connect(tableWidget,SIGNAL(itemChanged(QTableWidgetItem*)),SLOT(update(QTableWidgetItem*)));
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));
}
void MagicTable::setTable()
{
	for(int i=0;i<12;i++){
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setText(QString::number(0.000));
		tableWidget->setItem(0,i,item);
	}
 	tableWidget->resizeColumnsToContents();
}
void MagicTable::setLosses(const QVector<double> &a)
{
    losses = a;
    //qDebug()<<"MT setLosses"<< losses;
    doNotUpdate = true;
    updateTable();
    doNotUpdate = false;
}
void MagicTable::updateTable()
{

    for(int i=0;i<12;i++){
        tableWidget->item(0,i)->setText(QString::number(losses.at(i)));

    }

}

void MagicTable::clearTable()
{
	int a;
	a = losses.size();
	losses.resize(0);
	for(int i=0;i<a;i++){
		losses<<0;
		if (i<tableWidget->columnCount())
			tableWidget->item(0,i)->setText(QString::number(0));
	}
tableWidget->resizeColumnsToContents();
}
void MagicTable::clearSelected()
{
	QList<QTableWidgetSelectionRange> sel = tableWidget->selectedRanges();
	
	for(int k=0;k<sel.size();k++){
		for(int m=sel.at(k).leftColumn();m<=sel.at(k).rightColumn();m++){
			losses.replace(m,0);
			tableWidget->item(0,m)->setText(QString::number(0));
		}
	
}
  tableWidget->resizeColumnsToContents();
}
void MagicTable::update(QTableWidgetItem* i)
{
        //qDebug()<<"MT update before"<<losses<<i->data(0).toDouble()<<i->column();
    if (!doNotUpdate){
	if (i->column()<=losses.size()){
		losses.replace(i->column(),i->data(0).toDouble());
                //qDebug()<<"MT update after"<<losses<<i->data(0).toDouble()<<i->column();
		dirty=true;
}
    }
}
void MagicTable::uniformize()
{
	QList<QTableWidgetSelectionRange> sel = tableWidget->selectedRanges();
	double value= tableWidget->item(0,sel.at(0).leftColumn())->data(0).toDouble();

        //qDebug()<<"MT value"<<value;
	lossesUndo = losses;
	for(int k=0;k<sel.size();k++){
		for(int m=sel.at(k).leftColumn();m<=sel.at(k).rightColumn();m++){
			losses.replace(m,value);
			tableWidget->item(0,m)->setText(QString::number(value));
		}
	
}
  tableWidget->resizeColumnsToContents();
dirty = true;
}
void MagicTable::createActions()
{ 
	a_clear = new QAction(tr("Azzera"),this);
	a_clear->setToolTip(tr("Azzera tutte le celle selezionate"));
	connect(a_clear,SIGNAL(triggered()),SLOT(clearSelected()));
	
	a_copy = new QAction(tr("Copia"),this);
	a_copy->setToolTip(tr("Copia il primo valore della selezione su tutte le celle selezionate"));
	connect(a_copy,SIGNAL(triggered()),SLOT(uniformize())); 
}
void MagicTable::popUpMenu(const QPoint& a)
{

	QMenu menu;
	
	
	menu.addAction(a_clear);
	menu.addAction(a_copy);
	menu.exec(QCursor::pos());
	
}
QVector<double> MagicTable::getLosses()
{
	return losses;
}
bool MagicTable::isDirty()
{
	
}
void MagicTable::makeDirty(bool i)
{
	dirty =i;
}
