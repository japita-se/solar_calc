#include "albedo.h"
#include <QStandardItemModel>
#include <QDebug>
 #include <QHeaderView>
Albedo::Albedo(QWidget* parent): QDialog(parent)
{
	setupUi(this);
	createValues();
	createModel();
	groupBox->setEnabled(false);
	connect(tableAlbedo,SIGNAL(clicked(const QModelIndex &)),SLOT(setAlbedo(const QModelIndex &)));
	connect(tableAlbedo,SIGNAL(doubleClicked(const QModelIndex &)),SLOT(setAlbedoAndExit(const QModelIndex &)));
	connect(this,SIGNAL(accepted()),SLOT(setAlbedoType()));
	connect(radioValori,SIGNAL(toggled(bool)),SLOT(enableSnow(bool)));
	enableSnow(true);
// 	connect(radioMontagna,SIGNAL(toggled(bool)),SLOT(enableSnow(bool)));
					
}
void Albedo::enableSnow(bool i)
{
	if (i){
	 if (groupBox){
		groupBox->setEnabled(false);
		groupBox->setVisible(false);
		tableAlbedo->setVisible(true);
	}
	}
	else
	 if (groupBox){
		groupBox->setEnabled(true);
		groupBox->setVisible(true);
		tableAlbedo->setVisible(false);
	}
	
}
void Albedo::setAlbedoType(int m)
{
	
	if (m>=con & m<=variable_low_snow)
		albedoModel = m;
	if (m==con)
		radioValori->setChecked(true);
	if (m==variable_high_snow){
		
		radioMontagna->setChecked(true);
		radioSnowHigh->setChecked(true);
	}
	if (m==variable_low_snow){
		
		radioMontagna->setChecked(true);
		radioSnowLow->setChecked(true);
	}
	
	}
void Albedo::setAlbedo()
{
	QModelIndex m = tableAlbedo->currentIndex();
	if (m.isValid())
	albedo = albedoValue.at(m.row()).toDouble();
	else
	albedo = 0;
}
void Albedo::setAlbedo(double a)
{
	albedo = a;
}
void Albedo::setAlbedoAndExit(const QModelIndex &m)
{
	
	emit this->accepted();
	this->accept();
}
void Albedo::setAlbedo(const QModelIndex &m)
{
	if (m.isValid())
	albedo = albedoValue.at(m.row()).toDouble();
	
	
}
int Albedo::getAlbedoModel()
{
	return albedoModel;
}
void Albedo::setAlbedoType()
{
	if (radioValori->isChecked()){
		setAlbedo();
		albedoModel = con;
	}
	if (radioMontagna->isChecked()){
		if (radioSnowHigh->isChecked())
			albedoModel = variable_high_snow;
		if (radioSnowLow->isChecked())
			albedoModel =  variable_low_snow;
	}
}
double Albedo::getAlbedo()
{
	return albedo;
}
void Albedo::createValues()
{
	albedoType <<tr("Neve (caduta di fresco o con film di ghiaccio)")<<
		     tr("Superfici acquose")<<
		     tr("Suolo (creta, marne)")<<
		     tr("Strade sterrate")<<
		     tr("Bosco di conifere d'inverno")<<
		     tr("Bosco in autunno-Campi con raccolti maturi e piante")<<
		     tr("Asfalto invecchiato")<<
		     tr("Calcestruzzo invecchiato")<<
		     tr("Foglie morte")<<
		     tr("Erba secca")<<
		     tr("Erba verde")<<
		     tr("Tetti o terrazze in bitume")<<
		     tr("Pietrisco")<<
		     tr("Superfici scure di edifici (mattoni scuri, vernici scure, ...)")<<
		     tr("Superfici chiare di edifici (mattoni chiari, vernici chiare, ...)");
	albedoValue<<"0.75"<<
		     "0.07"<<
		     "0.14"<<
		     "0.04"<<
		     "0.07"<<
		     "0.26"<<
		     "0.10"<<
		     "0.22"<<
		     "0.30"<<
		     "0.20"<<
		     "0.26"<<
		     "0.13"<<
		     "0.20"<<
		     "0.27"<<
		      "0.60";
}

void Albedo::createModel()
{	
// 	qDebug()<<albedoType.size();

  	model = new QStandardItemModel(albedoType.size(),2);
  	for (int row=0;row<albedoType.size();row++)
 	{
 		QStandardItem *item1= new QStandardItem(albedoType.at(row));
// 		item1->setFlags(Qt::ItemIsSelectable);
  		QStandardItem *item2= new QStandardItem(albedoValue.at(row));
  		model->setItem(row,0,item1);
  			model->setItem(row,1,item2);
  	}
 	tableAlbedo->setModel(model);
	model->setHeaderData(0,Qt::Horizontal,tr("Tipo di ambiente"));
	model->setHeaderData(1,Qt::Horizontal,tr("Valore"));
	tableAlbedo->setWordWrap(true);
// 	tableAlbedo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	tableAlbedo->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
	tableAlbedo->horizontalHeader()->setMovable(true);
	tableAlbedo->horizontalHeader()->setStretchLastSection(false);
	tableAlbedo->setEditTriggers(QAbstractItemView::NoEditTriggers);
// 	tableAlbedo->
}
 Albedo::~Albedo()
{
	delete model;
}
