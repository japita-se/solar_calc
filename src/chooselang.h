#ifndef CHOOSELANG_H
#define CHOOSELANG_H

#include "ui_chooselang.h"

class ChooseLang : public QDialog, public Ui::ChooseLang
{
	Q_OBJECT
public:
        ChooseLang(QWidget* parent=0,int version=0);
	~ChooseLang();
	void setLanguage(int i);
	
	int getLang();
private slots:
	 void setLang(int i);
private:
	int language;
};
#endif
