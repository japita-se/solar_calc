#ifndef SHOEMESSAGE_H
#define SHOEMESSAGE_H
#include <QtGui>


class ShowMessage : QWidget
{
public:
    ShowMessage(QWidget* parent=0);
    void setMessage(const QString &a);
    void showMessage();
private:
    QString message;
};

#endif // SHOEMESSAGE_H
