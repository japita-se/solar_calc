//#define DEBUG
#include "settings.h"
#include <QDebug>
Settings::Settings(QWidget *parent ) : QDialog(parent)

{	/*u<<tr("[MJ/m2 giorno]")<<tr("[kWh/m2 giorno]");*/
	
	setupUi(this);
	 
	setWindowFlags(Qt::Tool|Qt::MSWindowsFixedSizeDialogHint);
	unit = 1;//MJ default
	radioMJ->setChecked(true);
	connect(radioMJ,SIGNAL(toggled(bool)),SLOT(updateUnita(bool)));
	connect(lineAsseX,SIGNAL(textChanged(const QString & )),SLOT(updateAxisX(const QString)));
	connect(lineAsseY,SIGNAL(textChanged(const QString & )),SLOT(updateAxisY(const QString)));
	connect(lineTitolo,SIGNAL(textChanged(const QString & )),SLOT(updateTitle( const QString &  )));
}

void Settings::setTitle(const QString &s)
{
	#ifdef DEBUG
	qDebug()<<"update titolo"<<getTitle();	
	#endif
        title = s;
        lineTitolo->setText(title);
}

 void Settings::updateTitle(const QString &s)
{
	#ifdef DEBUG
	qDebug()<<"update titolo"<<getTitle();	
	#endif
	title = s;
}
void Settings::setAxisX(const QString &s)
{
	axisX = s;
	lineAsseX->setText(axisX);
}
void Settings::updateAxisX(const QString &s)
{
	axisX = s;
}

void Settings::setAxisY(const QString &s)
{
	axisY = s ;;
	lineAsseY->setText(axisY);

}
void Settings::setAxisYRight(const QString &s)
{
	axisYRight = s ;;
	lineAsseYRight->setText(axisYRight);

}
void Settings::updateAxisY(const QString &s)
{
	axisY = s  ;
}
void Settings::setUnit(int i)
{
	/* set unit from extern */
	unit = i;
	if (unit==1)
		radioMJ->setChecked(true);
	if (unit==2)
		radiokWh->setChecked(true);
	
}
void Settings::updateUnita(bool i)
{
	if (radioMJ->isChecked())
		unit = 1;//MJ
	if (radiokWh->isChecked())
		unit = 2; //kWh


	#ifdef DEBUG
	qDebug()<<"update unita"<<unit;	
	#endif
	  
}
void Settings::setUnita(bool i)
{
	if (radioMJ->isChecked())
		unit = 1;//MJ
	if (radiokWh->isChecked())
		unit = 2; //kWh
}
 QString Settings::getTitle()
{
	return title;
}
QString Settings::getAxisX()
{
	return axisX ;
}
QString Settings::getAxisY( )
{
	return axisY ;
}
QString Settings::getAxisYRight( )
{
	return axisYRight ;
}
int Settings::getUnit( )
{
	return unit;
}
Settings::~Settings()
{
}
