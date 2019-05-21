#include "shoemessage.h"

ShowMessage::ShowMessage(QWidget *parent) {

}
void ShowMessage::setMessage(const QString &a)
{
    message = a;
}
void ShowMessage::showMessage()
{
    QMessageBox::critical(this,tr("Errore"),message);
}
