#ifndef _ASKUI_
#define _ASKUI_

#include "ui_ask.h"
 

class Ask : public QDialog, public Ui::Ask
{

	Q_OBJECT
public:
	Ask(QWidget *parent =0 );
	 
	
	 
	bool onlyCurrentMonth();
	bool doNotAskAgain();
	

private slots:
	void setOnlyCurrentMonth();
	void setAllMonths();
	void setDoNotAsk();
private:
	bool doNot,oneMonth;
};
#endif
