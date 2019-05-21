#include "infodialog.h"

InfoDialog::InfoDialog(QWidget* parent): QDialog(parent) {
	setupUi(this);
	dirty = false;
	connect(textEdit,SIGNAL(textChanged()),SLOT(update()));

}
void InfoDialog::update()
{
	infoString = textEdit->toPlainText();
	dirty = true;
}
void InfoDialog::setString(QString &q)
{
	infoString = q;
     //  infoString.toUtf8();
        textEdit->setPlainText(infoString);
	dirty = true;
}

bool InfoDialog::isDirty()
{
	return dirty;
}
void InfoDialog::makeDirty(bool i)
{
	dirty =i;
}
QString InfoDialog::getString()
{
	return textEdit->toPlainText();
}
