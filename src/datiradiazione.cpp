#include "datiradiazione.h"
#include <QDebug>
#include <QPointF>
#include <QPolygonF>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
DatiRadiazione::DatiRadiazione(QWidget *parent): QDialog(parent)
{
	setupUi(this);
	dirty = false;
	recentDir = QDir::homePath();
        status = radioEnea->isChecked() + 2*radioCustom->isChecked() +  8*radioNasa->isChecked();
	
	connect(radioEnea,SIGNAL(toggled(bool)),SLOT(emitSignal(bool)));
	connect(radioCustom,SIGNAL(toggled(bool)),SLOT(emitSignal(bool)));
        //connect(radioPvgis,SIGNAL(toggled(bool)),SLOT(emitSignal(bool)));
	connect(radioNasa,SIGNAL(toggled(bool)),SLOT(emitSignal(bool)));
	connect(linePath,SIGNAL(textChanged(const QString &)),SLOT(setDirty()));
// 	connect(this,SIGNAL(accepted()),SLOT(update()));
}
void DatiRadiazione::emitSignal(bool i)
{
        int temp = radioEnea->isChecked() + 2*radioCustom->isChecked() +  radioNasa->isChecked()*8;
	if (temp!=status) {
		dirty = true;
// 		qDebug()<<"RadSettings"<<status<<temp;
		status = temp;
		}
	
	
}
void DatiRadiazione::setDirty(bool state)
{
	dirty = state;
}
void DatiRadiazione::setDirty()
{
	dirty = true;
}
bool DatiRadiazione::isDirty()
{
	return dirty;
}
// void DatiRadiazione::update()
// {
// 	if (isDirty) {
// 	qDebug()<<"Emetto sorgenteChanged()";
// 		emit sorgenteChanged();
// 	}
// }
DatiRadiazione::~DatiRadiazione()
{
}
void DatiRadiazione::on_pushCarica_clicked()
{
	loadCustomRad(QString());
}
void DatiRadiazione::loadCustomRad(const QString &name )
{
	QString fileName;
	if (name.isEmpty() || name.isNull()) {
		
		fileName = QFileDialog::getOpenFileName(this, tr("File radiazione"), recentDir, "Text files (*.txt  )");
	}
	else
	 fileName = name;
    	
	QPolygonF temp;
	int condition;
	double x,y;
	condition = 0;
    	if ( !fileName.isEmpty() )
    	{ 
                QFile file(fileName);
                QFileInfo fileInfo(fileName);
                recentDir = fileInfo.absoluteDir().absolutePath();
		QTextStream in(&file);
		if (file.open(QIODevice::ReadOnly)){
			while (!in.atEnd()) {
				QString lineRaw =in.readLine();
				lineRaw = lineRaw.simplified();
				QStringList l = lineRaw.split(" ");

				if ( (l.size()<2) && (!lineRaw.isEmpty())) {
                                        QMessageBox::critical(this,tr("Importazione"),tr("Il file di dati deve avere almeno due colonne."),QMessageBox::Ok);

					return;
				}
				else 
				{
					if (!lineRaw.isEmpty()) {
						x = l.at(0).toDouble();
						y = l.at(1).toDouble();
                                                if (y<0) {
							condition++;
                                                        y = 0;
                                                         }
                                                temp<<QPointF(x,y);

					}
                                }
			}
				if (condition>0) {
					int response =QMessageBox::question(this,tr("Importazione radiazione"),tr("Il file contiene valori negativi. Se si continua, i risultati non saranno significativi.Continuare?"),QMessageBox::Ok,QMessageBox::Cancel);
					
					if (response==QMessageBox::Ok) 
					{
						
						customHg.resize(0);
						customHg = temp;
						
 					}
					else {
						updateLinePath(fileName);
						return ;
					     }
				}	
				else
				{
					if (temp.size()!=12) {
						int r2 = QMessageBox::question(this,tr("Errore"),tr("Il file contiene un numero di mesi diverso da 12. Se si continua, i mesi mancanti avranno radiazione nulla."),QMessageBox::Ok,QMessageBox::Cancel);
						if (r2=QMessageBox::Ok){
							 customHg = temp;
							 resizeCustomHg(temp.size());
							 updateLinePath(fileName);
						}
						else
							return;
					}
					else {
						customHg.resize(0);
						customHg = temp;
						updateLinePath(fileName);
					}
				}
			 				
		}
	}		
}
void DatiRadiazione::resizeCustomHg(int s)
	
{
		if (s>12)
			customHg.resize(12);
			
		if (s<12) {
			for (int i=s;i<12-customHg.size();i++)
				customHg.append(QPointF(i,0));
		}	
	qDebug()<<"Dati radiazione resize..."<<customHg;
}
void DatiRadiazione::updateLinePath(const QString &s)
{
	linePath->setText(s);
	sourceName = s;
}
QPolygonF DatiRadiazione::getCustomHg()
{	
	return customHg;
}
QString DatiRadiazione::getSourceName()
{
	return sourceName;
}
