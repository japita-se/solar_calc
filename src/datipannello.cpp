#include "datipannello.h"
#include "doubledelegate.h"
#include "myfilter.h"
#include <QSqlTableModel>
#include <QTableView>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QSqlQuery>
#include <QSqlError>




DatiPannello::DatiPannello(QWidget* parent): QDialog(parent)
{
	setupUi(this);
        setupActions();
        model       = new QSqlTableModel(this);
        listModel   = new QStringListModel(this);
        proxyListModel = new QSortFilterProxyModel(this);
        proxyModel  = new MyFilterProxyModel(this);
	proxyModel->setDynamicSortFilter(true);
	connect(lineSearch,SIGNAL(textChanged(const QString&)),this,SLOT(setFilter(const QString&)));
// 	tViewDatiPannello->setSelectionMode(QAbstractItemView::SingleSelection);
	
	 QVector<int> d(5);
	d<<19<<18<<11<<12<<13;
        tViewDatiPannello->setItemDelegate(new DoubleDelegate(d,100,-100,2));
	
 
// 	connect(model,SIGNAL(beforeUpdate(int,QSqlRecord &)),SLOT(beforeUpdate(int,QSqlRecord&)));
	connect(tViewDatiPannello,SIGNAL(doubleClicked(const QModelIndex &)),SLOT(enableApply(const QModelIndex&)));
	connect(this,SIGNAL(accepted()),SLOT(getPanel()));
	connect(comboFilter,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(setFilter(const QString &)));
	connect(lineSearch,SIGNAL(editingFinished()),SLOT(getPanel()));
	connect(pushApplica,SIGNAL(clicked()),SLOT(submitChange()));
	
	pushApplica->setEnabled(false);

	connect(pushDelete,SIGNAL(clicked()),SLOT(deleteRow()));

        connect(listMarca,SIGNAL(clicked(QModelIndex)),SLOT(setFilter(QModelIndex)));
        listMarca->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(listMarca,SIGNAL(customContextMenuRequested(const QPoint &  )),this,SLOT(popUpMenu(const QPoint &)));

}
void DatiPannello::setupActions()
{
    a_delete = new QAction(tr("Elimina"),this);
    connect(a_delete,SIGNAL(triggered()),SLOT(deleteMarca()));
}

void DatiPannello::popUpMenu(const QPoint& point)
{


    QMenu menu;

    menu.addAction(a_delete);

   #ifdef Q_WS_X11
    menu.popup(pos);
    #endif
    menu.exec(QCursor::pos());
}
void DatiPannello::deleteMarca()
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
query.prepare("DELETE FROM pannelli WHERE costruttore='"+deleteSet.join("")+"'");
query.exec();
qDebug()<<"Datipannello delete marca"<<query.lastError()<<query.executedQuery();
modelsPV.removeAt(modelsPV.indexOf(deleteSet.join("")));
qDebug()<<"DP"<<modelsPV;
refreshView();

}

void DatiPannello::deleteRow()
{
        QSqlRecord c;
	QString deleteSet = "(";
	int question = QMessageBox::question(this,tr("SolarCalc - Cancella pannello"),tr("Sei sicuro di voler cancellare il pannello?"),QMessageBox::Ok,QMessageBox::Cancel);
        if (question==QMessageBox::Ok) {
		QModelIndexList toCutIndex = tViewDatiPannello->selectionModel()->selectedIndexes();
               qDebug()<<"DP"<<tViewDatiPannello->selectionModel()->selectedIndexes();
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
	  
	 query.prepare("DELETE FROM pannelli WHERE id in "+deleteSet);
	 query.exec();
// 	 qDebug()<<"Datipannello dleterow"<<query.lastError();
	 initializeModel();
	 refreshView();

}
}
void DatiPannello::submitChange()
{
        currentIndex = tViewDatiPannello->currentIndex();
        beforeUpdate(currentIndex.row());
	model->submitAll();
	pushApplica->setEnabled(false);
        //qDebug()<<"submit in datipannello"<<model->submitAll()<<model->database().tables()<<table;
	
}
void DatiPannello::setDatabase(const QSqlDatabase &db,const QString &t)
{
	database = db;	
	table = t;
        if (model!=0){
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
void DatiPannello::refreshView()
{	
		initializeModel();
	
		proxyModel->setSourceModel(model);
                proxyListModel->setSourceModel(listModel);
                proxyListModel->sort(0,Qt::AscendingOrder);
                listMarca->setModel(proxyListModel);
		tViewDatiPannello->setModel(proxyModel);
		
                 tViewDatiPannello->setColumnHidden(0,true);
                 tViewDatiPannello->setColumnHidden(1,true);
//                tViewDatiPannello->verticalHeader()->setItemDelegateForColumn(1,new TextDelegate);
//                 tViewDatiPannello->verticalHeader()->setItemDelegateForColumn(2,new TextDelegate);
                tViewDatiPannello->resizeColumnsToContents();


		 
		 
}
void DatiPannello::initializeModel()
{
    QString temp;
        if (model!=0) {
 		model->setTable(table);
                model->setEditStrategy(QSqlTableModel::OnRowChange);
 		model->select();
		 
//       		model->removeColumn(0);

                model->setHeaderData(1, Qt::Horizontal, tr("Marca"),Qt::DisplayRole);
                model->setHeaderData(2, Qt::Horizontal, QObject::tr("Modello"));
                model->setHeaderData(3, Qt::Horizontal, tr("Pnom")+"(Wp)");
                model->setHeaderData(4, Qt::Horizontal, tr("Voc")+"(V)");
                model->setHeaderData(5, Qt::Horizontal, tr("Isc")+"(A)");
                model->setHeaderData(6, Qt::Horizontal, tr("Imp")+"(A)");
		model->setHeaderData(7, Qt::Horizontal, tr("NOCT"));
                model->setHeaderData(8, Qt::Horizontal, tr("Peso")+"(Kg)");
                model->setHeaderData(9, Qt::Horizontal, tr("Vmp")+"(V)");
                model->setHeaderData(10, Qt::Horizontal, tr("Vmax")+"(V)");
                model->setHeaderData(11, Qt::Horizontal, tr("beta(Voc)")+"(%/C)");
                model->setHeaderData(12, Qt::Horizontal, tr("alfa(Isc)")+"(%/C)");
                model->setHeaderData(13, Qt::Horizontal, tr("gamma(Pnom)")+"(%/C)");
		model->setHeaderData(14, Qt::Horizontal, tr("tol."));
                model->setHeaderData(15, Qt::Horizontal, tr("H")+"(mm)");
                model->setHeaderData(16, Qt::Horizontal, tr("L")+"(mm)");
                model->setHeaderData(17, Qt::Horizontal, tr("s")+"(mm)");
                model->setHeaderData(18, Qt::Horizontal, tr("efficienza")+"%");
                model->setHeaderData(19, Qt::Horizontal, tr("usura/anno")+"%");

	}
        if (listModel!=0){

            listModel->setStringList(modelsPV);
            QSqlQuery q(database);
            q.prepare("SELECT costruttore FROM pannelli");
            q.exec();

            while (q.next()){

                temp = q.value(0).toString();
                if (!modelsPV.contains(temp))
                    modelsPV << temp;
            }

             listMarca->setModel(proxyListModel);
        }
	
	
 
	
}
void DatiPannello::setFilter(const QString &filtro)
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
        QRegExp regExp(filtro, Qt::CaseInsensitive, QRegExp::PatternSyntax(QRegExp::FixedString));
        proxyModel->setFilterRegExp(regExp);

}
void DatiPannello::setFilter(const QModelIndex &a)
{

    sourceString = listModel->data(proxyListModel->mapToSource(a),Qt::DisplayRole).toString();

    setFilter(lineSearch->text());
}

DatiPannello::~DatiPannello()
{
}
panel DatiPannello::getSelectedPanel()
{
	return out;
}
panel DatiPannello::getSelectedPanel(int row)
{
	model->setFilter("id="+QString::number(row));
	model->select();
	 if (row>0) {
	 
	out.fabric = model->record(0).value("costruttore").toString();
	out.model  = model->record(0).value("modello").toString();
	 out.voc = model->record(0).value("voc").toDouble();
	out.vmp = model->record(0).value("vmp").toDouble(); 
	out.isc  = model->record(0).value("isc").toDouble();
	out.vmax = model->record(0).value("vmax").toDouble();
	out.imp  = model->record(0).value("imp").toDouble();
	out.noct = model->record(0).value("noct").toDouble();
	out.alfa  = model->record(0).value("alfa").toDouble();
	out.beta = model->record(0).value("beta").toDouble();
	out.gamma= model->record(0).value("gamma").toDouble();
	out.H    = model->record(0).value("h").toDouble();
	out.L    = model->record(0).value("l").toDouble();
	out.s    = model->record(0).value("s").toDouble();
	out.pnom = model->record(0).value("pnom").toDouble();
	out.eff  = model->record(0).value("efficienza").toDouble();
	out.gar  = model->record(0).value("usura").toDouble();
	out.indexDB = model->record(0).value("id").toInt();
	out.isValid = true;
	 
	}
	else
	{
	out.isValid = false;
	 
	}
        //#ifdef DEBUG
        qDebug()<<"DatiPannello panel valid"<<row<<out.isValid<<out.indexDB<<model->query().lastError()<<model->filter()<<row;
        //#endif
	return out;
}
 void DatiPannello::getPanel()
{
     /* DEBUG FOR XP*/


     /*******************/

        currentIndex = proxyModel->mapToSource(tViewDatiPannello->currentIndex());
	if (currentIndex.isValid()) {


        QSqlRecord r = model->record(currentIndex.row());
        qDebug()<<"DATI PANNELLO"<<currentIndex<<r.field("id")<<r;

	out.fabric = r.value("costruttore").toString();
	out.model  = r.value("modello").toString();
	 out.voc = r.value("voc").toDouble();
	out.vmp = r.value("vmp").toDouble(); 
	out.isc  = r.value("isc").toDouble();
	out.vmax = r.value("vmax").toDouble();
	out.imp  = r.value("imp").toDouble();
	out.noct = r.value("noct").toDouble();
	out.alfa  = r.value("alfa").toDouble();
	out.beta = r.value("beta").toDouble();
	out.gamma= r.value("gamma").toDouble();
	out.H    = r.value("h").toDouble();
	out.L    = r.value("l").toDouble();
	out.s    = r.value("s").toDouble();
	out.pnom = r.value("pnom").toDouble();
	out.eff  = r.value("efficienza").toDouble();
	out.gar  = r.value("usura").toDouble();
        //out.indexDB = r.value(r.fieldName(r.indexOf("id"))).toInt();

        //There is a bug in Qt 4.7
        out.indexDB = currentIndex.row()+1;
        ///////////////////////////
	out.isValid = true;
	 
	}
	else
	{
	out.isValid = false;
	 
	}
	
}
void DatiPannello::beforeUpdate(int row)
{	
	QSqlRecord record;
	record = model->record(row);
	int r;

	int error1=0,error2=0;
	double eff = record.value("efficienza").toDouble();
	int   effIndex = record.indexOf("efficienza");
	double H   = record.value("h").toDouble();
	double l   = record.value("l").toDouble();
	double p   = record.value("pnom").toDouble();
	double area = (H*l)/1000000;/* area in mq*/
	double gar  = record.value("usura").toDouble();
	double trueEff=(p/(1000*area)) *100;
        //qDebug()<<"DatiPannello before Insert"<<eff<<p <<H<<l;

        if (fabs(eff - trueEff)>0.000000002)
		error1 = 1;
	if ( gar<0 || gar > 100 )
		error2 = 1;

	switch (error1+2*error2) {
		case 0:
		break;
		case 1:
		
 			 r = QMessageBox::question(this,tr("Efficienza errata"),tr("Hai inserito un'efficienza che sembra errata rispetto alle dimensioni del pannello e alla Pnom. Calcolo l'efficienza?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
			if (r==QMessageBox::Yes){
				model->setData(model->index(row,effIndex),trueEff);
                                qDebug()<<"Update eff "<<model->index(row,effIndex)<<trueEff<<p<<area<<H<<l<<trueEff-eff;
			}
		
		break;
		case 2:
		
		QMessageBox::warning(this,tr("Usura errata"),tr("Hai inserito una riduzione d'efficienza fuori dall'intervallo (0-100%). Ricontrolla."),QMessageBox::Ok);
		break;
	}
	
}
void DatiPannello::enableApply(const QModelIndex &y)
{
        currentIndex = y ;
	pushApplica->setEnabled(true);
}
