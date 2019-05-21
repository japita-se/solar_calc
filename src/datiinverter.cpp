#include "myfilter.h"
#include "datiinverter.h"
#include "doubledelegate.h"
#include "combodelegate.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QSqlQuery>
#include <QSqlError>
DatiInverter::DatiInverter(QWidget* parent): QDialog(parent)
{
	setupUi(this);
        setupActions();
	model = new QSqlTableModel;
        listModel   = new QStringListModel(this);
        proxyListModel = new QSortFilterProxyModel(this);
        proxyModel  = new MyFilterProxyModel(this);
	proxyModel->setDynamicSortFilter(true);
	connect(lineSearch,SIGNAL(textChanged(const QString&)),this,SLOT(setFilter(const QString&)));
        QVector<int> d(5),c(1,12);
        d<<10<<11<<12<<13;
        QStringList types;
        types << tr("Monofase")<<tr("Trifase");
 	tViewDatiInverter->setItemDelegate(new DoubleDelegate(d,100,0,2));
        tViewDatiInverter->setItemDelegate(new ComboDelegate(c,types));
        connect(model,SIGNAL(beforeUpdate(int,QSqlRecord &)),SLOT(beforeUpdate(int,QSqlRecord&)));
	connect(tViewDatiInverter,SIGNAL(doubleClicked(const QModelIndex &)),SLOT(enableApply(const QModelIndex&)));
	 
	connect(this,SIGNAL(accepted()),SLOT(getInverter()));
	connect(comboFilter,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(setFilter(const QString &)));
	connect(lineSearch,SIGNAL(editingFinished()),SLOT(getInverter()));
	connect(pushApplica,SIGNAL(clicked()),SLOT(submitChange()));
	
	pushApplica->setEnabled(false);

	connect(pushElimina,SIGNAL(clicked()),SLOT(deleteRow()));
         connect(listMarca,SIGNAL(clicked(QModelIndex)),SLOT(setFilter(QModelIndex)));
         listMarca->setContextMenuPolicy(Qt::CustomContextMenu);
         connect(listMarca,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));
}
void DatiInverter::setupActions()
{
    a_delete = new QAction(tr("Elimina"),this);
    connect(a_delete,SIGNAL(triggered()),SLOT(deleteMarca()));
}
void DatiInverter::popUpMenu(const QPoint& point)
{


    QMenu menu;

    menu.addAction(a_delete);

   #ifdef Q_WS_X11
    menu.popup(pos);
    #endif
    menu.exec(QCursor::pos());
}
void DatiInverter::deleteMarca()
{
    QSqlRecord c;

    QStringList deleteSet;
    QModelIndexList toCutIndex = listMarca->selectionModel()->selectedIndexes();
 qDebug()<<toCutIndex;

    for(int i=0;i<toCutIndex.size();i++) {


    deleteSet << listModel->data(proxyListModel->mapToSource(toCutIndex.at(i)),Qt::EditRole).toString();
    listModel->removeRows(proxyListModel->mapToSource(toCutIndex.at(i)).row() ,1);


    qDebug()<<toCutIndex<<proxyListModel->mapToSource(toCutIndex.at(i)).row();
}


QSqlQuery query(database);
query.prepare("DELETE FROM inverter WHERE costruttore='"+deleteSet.join("")+"'");
query.exec();
//qDebug()<<"Datipannello delete marca"<<query.lastError()<<query.executedQuery();
modelsInv.removeAt(modelsInv.indexOf(deleteSet.join("")));
//qDebug()<<"DP"<<modelsInv;
refreshView();

}
void DatiInverter::deleteRow()
{
        QSqlRecord c;
	QString deleteSet = "(";
	int question = QMessageBox::question(this,tr("SolarCalc - Cancella inverter"),tr("Sei sicuro di voler cancellare l' inverter?"),QMessageBox::Ok,QMessageBox::Cancel);
        if (question==QMessageBox::Ok) {
		QModelIndexList toCutIndex = tViewDatiInverter->selectionModel()->selectedIndexes();
		 for(int i=0;i<toCutIndex.size();i++) {

                       c = model->record(proxyModel->mapToSource(toCutIndex.at(i)).row());
			 #ifdef DEBUG
                        qDebug()<<toCutIndex.at(i).row()<<c.value(0);
                        #endif

                                if (i>0)
				deleteSet += "," + c.value(0).toString();
                                else
                                deleteSet += c.value(0).toString();
                }
	 deleteSet += ")";

 	 QSqlQuery query(database);
	  
	 query.prepare("DELETE FROM inverter WHERE id in "+deleteSet);
	 query.exec();

	 initializeModel();
	 refreshView();

}
}
 
void DatiInverter::submitChange()
{
	model->submitAll();
	pushApplica->setEnabled(false);
// 	qDebug()<<"submit in datipannello"<<model->submitAll()<<model->database().tables()<<table;
	
}
void DatiInverter::setDatabase(const QSqlDatabase &db,const QString &t)
{
	database = db;	
	table = t;
	if (model){
		delete model;
		model = new QSqlTableModel(0,database);
	}
        if (listModel!=0) {
            delete listModel;
            listModel = new QStringListModel(this);

        }
	initializeModel();
	refreshView();
	 
}
void DatiInverter::refreshView()
{	
	initializeModel();
	
		proxyModel->setSourceModel(model);

                proxyListModel->setSourceModel(listModel);
                //proxyListModel->sort(0,Qt::AscendingOrder);
                listMarca->setModel(proxyListModel);
		tViewDatiInverter->setModel(proxyModel);
                tViewDatiInverter->setColumnHidden(0,true);
                tViewDatiInverter->setColumnHidden(1,true);

		 
}
void DatiInverter::initializeModel()
{
    QString temp;
	if (model) {
		model->setTable(table);
		 model->setEditStrategy(QSqlTableModel::OnManualSubmit);
 		 model->select();
 		
		 
// 		model->removeColumn(0);
		model->setHeaderData(1, Qt::Horizontal, tr("Marca"));
		model->setHeaderData(2, Qt::Horizontal, tr("Modello"));
		model->setHeaderData(3, Qt::Horizontal, tr("Pin"));
		model->setHeaderData(4, Qt::Horizontal, tr("Pnom"));
	/*	model->setHeaderData(5, Qt::Horizontal, tr("Isc"));
		model->setHeaderData(6, Qt::Horizontal, tr("Imp"));
		model->setHeaderData(7, Qt::Horizontal, tr("NOCT"));
		model->setHeaderData(8, Qt::Horizontal, tr("Peso"));*/	
		model->setHeaderData(5, Qt::Horizontal, tr("Vmax"));
		model->setHeaderData(6, Qt::Horizontal, tr("Vmin"));
		model->setHeaderData(7, Qt::Horizontal, tr("Vpmin"));
		model->setHeaderData(8, Qt::Horizontal, tr("Vpmax"));
		model->setHeaderData(9, Qt::Horizontal, tr("Imax"));
		model->setHeaderData(10, Qt::Horizontal, tr("efficienza"));
		model->setHeaderData(11, Qt::Horizontal, tr("usura"));
                model->setHeaderData(12, Qt::Horizontal, tr("tipo"));
                model->setHeaderData(13, Qt::Horizontal, tr("Vout"));
                model->setHeaderData(14, Qt::Horizontal, tr("Icc"));
                model->setHeaderData(15, Qt::Horizontal, tr("Trasf."));
                model->setHeaderData(16, Qt::Horizontal, tr("Cos(PHI)"));
// 		model->setHeaderData(14, Qt::Horizontal, tr("tol."));
// 		model->setHeaderData(15, Qt::Horizontal, tr("H"));
// 		model->setHeaderData(16, Qt::Horizontal, tr("L"));
// 		model->setHeaderData(17, Qt::Horizontal, tr("s"));
// 		model->setHeaderData(18, Qt::Horizontal, tr("efficienza"));
		 model->select();
	}
        if (listModel!=0){

            listModel->setStringList(modelsInv);
            QSqlQuery q(database);
            q.prepare("SELECT costruttore FROM inverter");
            q.exec();

            while (q.next()){

                temp = q.value(0).toString();
                if (!modelsInv.contains(temp))
                    modelsInv << temp;
            }

             listMarca->setModel(proxyListModel);
	 
}
    }
void DatiInverter::setFilter(const QString &filtro)
{
	int index;
	if (model)
		index = model->record().indexOf(comboFilter->currentText());
	else
		index = -1;
        /* Search in column at index and with MARCA = sourceString */
        proxyModel->setSourceString(sourceString);
        proxyModel->setSourceCol(index,1);//set the columns for searching
        //proxyModel->setFilterKeyColumn(index);
        qDebug()<<"DI SET FILTER"<<sourceString<<filtro<<comboFilter->currentText();
        QRegExp regExp(filtro, Qt::CaseInsensitive , QRegExp::PatternSyntax(QRegExp::FixedString));
        proxyModel->setFilterRegExp(regExp);

}
void DatiInverter::setFilter(const QModelIndex &a)
{

    sourceString = listModel->data(proxyListModel->mapToSource(a),Qt::DisplayRole).toString();

    setFilter(lineSearch->text());
}

DatiInverter::~DatiInverter()
{
}
inverter DatiInverter::getSelectedInverter()
{
	return inv;
}
inverter DatiInverter::getSelectedInverter(int row)
{
	model->setFilter("id="+QString::number(row));
	model->select();
	if (row>0) {
// 	QSqlRecord r = model->record( row );
	inv.fabric = model->record(0).value("costruttore").toString();
	inv.model  = model->record(0).value("modello").toString();
	inv.vmax =   model->record(0).value("vmax").toDouble();
	inv.vmin  =  model->record(0).value("vmin").toDouble();
	inv.vmpmin    = model->record(0).value("vmpmin").toDouble();
	inv.vmpmax   = model->record(0).value("vmpmax").toDouble();
	inv.imax   = model->record(0).value("imax").toDouble();
	inv.eff    = model->record(0).value("efficienza").toDouble();
	inv.gar    = model->record(0).value("usura").toDouble();
	inv.pnom = model->record(0).value("pnom").toDouble();
	inv.pin  = model->record(0).value("pin").toDouble();
	inv.indexDB = model->record(0).value("id").toInt();
        inv.type    = model->record(0).value("tipo").toString();
        inv.vout    = model->record(0).value("vout").toDouble();
        inv.icc    = model->record(0).value("tipo").toDouble();
        inv.trasformer=  model->record(0).value("tra").toBool();
        inv.cosphi=  model->record(0).value("cosphi").toDouble();
	inv.isValid = true;
// 	 qDebug()<<"Dati Inverter id"<<model->record(0).value("id").toInt()<<row;
	}
	else
	{
	inv.isValid = false;
	 
	}
	return inv;
}
 void DatiInverter::getInverter()
{
	 

         currentIndex = proxyModel->mapToSource(tViewDatiInverter->currentIndex());
	if (currentIndex.isValid()) {
	QSqlRecord r = model->record(currentIndex.row());
	inv.fabric = r.value("costruttore").toString();
	inv.model  = r.value("modello").toString();
	inv.vmax = r.value("vmax").toDouble();
	inv.vmin  = r.value("vmin").toDouble();
	inv.vmpmin    = r.value("vmpmin").toDouble();
	inv.imax   = r.value("imax").toDouble();
	inv.vmpmax   = r.value("vmpmax").toDouble();
	inv.eff    = r.value("efficienza").toDouble();
	inv.gar    = r.value("usura").toDouble();
	inv.pnom = r.value("pnom").toDouble();
	inv.pin  = r.value("pin").toDouble();

        // inv.indexDB = r.value("id").toInt();
        //There is a bug in Qt 4.7 in XP
        inv.indexDB = currentIndex.row()+1;
        ///////////////////////////
        inv.isValid = true;

        inv.type    = model->record(0).value("tipo").toString();
        inv.vout    = model->record(0).value("vout").toDouble();
        inv.icc    = model->record(0).value("icc").toDouble();
        inv.trasformer    = model->record(0).value("tra").toBool();
        inv.cosphi=  model->record(0).value("cosphi").toDouble();
	inv.isValid = true;
	 
	}
	else
	{
	inv.isValid = false;
	 
	}
	
}
void DatiInverter::beforeUpdate(int row,QSqlRecord &record)
{	
	
	double eff = record.value("efficienza").toDouble();
	double gar = record.value("usura").toDouble();
	 
	 
	if (eff<=0)
		QMessageBox::warning(this,tr("Efficienza errata"),tr("Hai inserito un'efficienza che sembra errata. Ricontrolla."),QMessageBox::Ok);
	if (gar<=0)
		QMessageBox::warning(this,tr("Garanzia errata"),tr("Hai inserito una garanzia che sembra errata. Ricontrolla."),QMessageBox::Ok);
	
}
void DatiInverter::enableApply(const QModelIndex &y)
{
	
	pushApplica->setEnabled(true);
}
// void DatiInverter::beforeUpdate(int row,QSqlRecord &record)
// {	
// 	
// 	double eff = record.value("efficienza").toDouble();
// 	double H   = record.value("h").toDouble();
// 	double l   = record.value("l").toDouble();
// 	double p   = record.value("pnom").toDouble();
// 	double area = (H*l)/1000000;/* area in mq*/
// 	qDebug()<<"DatiInverter beforet Insert"<<eff<<p <<H<<l;
// 	if ((p/1000*area)<eff)
// 		QMessageBox::warning(this,tr("Efficienza errata"),tr("Hai inserito un'efficienza che sembra errata rispetto alle dimensioni del pannello e alla Pnom. Ricontrolla."),QMessageBox::Ok);
// }
