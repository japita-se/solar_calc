/* version = 0 Community*/
/* version = 1 Plus o*/
#include "chooselang.h"

ChooseLang::ChooseLang(QWidget* parent,int version): QDialog(parent)
{
	setupUi(this);
	language = 0; /* default italian */
	comboLang->setCurrentIndex(0);
	connect(comboLang,SIGNAL(currentIndexChanged(int)),SLOT(setLang(int)));
	connect(okButton,SIGNAL(clicked()),SLOT(accept()));
if (version==0)
            comboLang->addItems(QStringList()<<tr("Italiano")<<tr("English"));



}
int ChooseLang::getLang()
{
	return language;
}
void ChooseLang::setLang(int i)
{
	language = i;
}

ChooseLang::~ChooseLang()
{}
