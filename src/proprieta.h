#ifndef PROPRIETA_H
#define PROPRIETA_H

#include "ui_proprieta.h"
#include <QNetworkProxy>

class Proprieta : public QDialog, public Ui::Proprieta
{
	Q_OBJECT
public:
        Proprieta(QWidget* parent=0,int version=0);
	~Proprieta();

        QString getHost();
        QString getUser();
        QString getPassword();
        int getType();
        QNetworkProxy getProxy();
        void setProxy(QNetworkProxy s);
        int getPorta();
        void setHost(const QString &a);
        void setUser(const QString &a);
        void setPassword(const QString &a);
        void setType(const QString &a);
        void setPorta(int a);
        bool proxyEn();



	void setLanguage(int i);

	
	int getLang();
        int getNumberOfDecimals();
public slots:
        void enableProxy(bool a);
        void updateNumOfDecimals( );
        void setNumOfDecimals(int i);
        void updateHost(const QString &a);
        void updateUser(const QString &a);
        void updatePassword(const QString &a);
        void updateType(int i);
        void updatePorta(int a);
private slots:

        void updateLang(int i);

private:
        QString language;
        bool proxyEnabled;
        int numOfDec;
        QNetworkProxy p;
};
#endif
