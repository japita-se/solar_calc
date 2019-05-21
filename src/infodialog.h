#ifndef INFODIALOG_H
#define INFODIALOG_H

#include "ui_info.h"

class InfoDialog : public QDialog, public Ui::DialogInfo
{
	Q_OBJECT
public:
	InfoDialog(QWidget* parent=0);
	void setString(QString &g);
	QString getString();
	bool isDirty();
	void makeDirty(bool i);
private slots:
	void update();
private:
	QString infoString;
	bool dirty;
	
};
#endif
	