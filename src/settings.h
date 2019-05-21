#ifndef _SETTINGSUI_
#define _SETTINGSUI_

#include "ui_settings.h"

class Settings : public QDialog, public Ui::Settings
{
	Q_OBJECT
public:
	Settings(QWidget *parent =0 );
	~Settings();
	void setTitle(const QString &s);
	void setAxisX(const QString &s);
	void setAxisY(const QString &s);
	void setAxisYRight(const QString &s);
	
	QString getTitle();
	QString getAxisX();
	QString getAxisY();
	QString getAxisYRight();
	int getUnit();
	void setUnit(int i);
private slots:
	void setUnita(bool i);
	void updateTitle(const QString &s);
	void updateAxisX(const QString &s);
	void updateAxisY(const QString &s);
	void updateUnita(bool i);
private:
	
private:
	QString title,axisX,axisY,axisYRight;
	int unit;
	
	
};
#endif

