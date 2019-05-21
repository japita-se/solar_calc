
#include "proprieta.h"
#include <QDebug>
#include <QNetworkProxy>

Proprieta::Proprieta(QWidget* parent,int version) : QDialog(parent)
{
	setupUi(this);

        p.setHostName("");
        p.setPassword("");
        p.setUser("");
        p.setPort(1080);
        p.setType(QNetworkProxy::DefaultProxy);
        proxyEnabled = false;
        groupProxy->setEnabled(false);
        connect(comboLang,SIGNAL(currentIndexChanged(int)),SLOT(updateLang(int)));
        connect(sNumOfDecimals,SIGNAL(valueChanged(int)),SLOT(setNumOfDecimals(int)));
        connect(checkProxy,SIGNAL(toggled(bool)),SLOT(enableProxy(bool)));
        connect(lineHost,SIGNAL(textChanged(QString)),SLOT(updateHost(QString)));
        connect(comboType,SIGNAL(currentIndexChanged(int)),SLOT(updateType(int )));
        connect(lineUser,SIGNAL(textChanged(QString)),SLOT(updateUser(QString)));
        connect(linePass,SIGNAL(textChanged(QString)),SLOT(updatePassword(QString)));
        connect(spinPorta,SIGNAL(valueChanged(int)),SLOT(updatePorta(int)));

	language = "italiano";
        numOfDec = 2;
        if (version==0)
            comboLang->addItems(QStringList()<<tr("Italiano")<<tr("English"));
        if (version==1)
                        comboLang->addItems(QStringList()<<tr("Italiano"));

//qDebug()<<"PROPRIETA VERSION"<<version<<comboLang->count();
}


void Proprieta::setType(const QString &a)
{
    comboType->setCurrentIndex(comboType->findText(a));
}
void Proprieta::setPassword(const QString &a)
{
    linePass->setText(a.simplified().trimmed());

}
void Proprieta::setUser(const QString &a)
{
    lineUser->setText(a.simplified().trimmed());
}
void Proprieta::setPorta(int a)
{
    spinPorta->setValue(a);
}
void Proprieta::setHost(const QString &a)
{
    lineHost->setText(a.simplified().trimmed());
}


void Proprieta::updateType(int i)
{
    p.setType((QNetworkProxy::ProxyType)(i));
}
void Proprieta::updatePassword(const QString &a)
{
    p.setPassword(a);

}
void Proprieta::updateUser(const QString &a)
{
    p.setUser(a);
}
void Proprieta::updatePorta(int a)
{
    p.setPort(a);
}
void Proprieta::updateHost(const QString &a)
{
    p.setHostName(a);
}
QString Proprieta::getHost()
{
    return p.hostName();
}
int Proprieta::getPorta()
{
    return p.port();
}
QString Proprieta::getUser()
{
    return p.user();
}
QString  Proprieta::getPassword()
{
    return p.password();
}
int Proprieta::getType()
{
    return p.type();
}
QNetworkProxy Proprieta::getProxy()
{
    return p;
}
void Proprieta::setProxy(QNetworkProxy s)
{
    p = s;
    lineUser->setText(p.user());
    linePass->setText(p.password());
    spinPorta->setValue(p.port());
    comboType->setCurrentIndex((int)(p.type()));
    lineHost->setText(p.hostName());

}

void Proprieta::enableProxy(bool i)
{

        groupProxy->setEnabled(i);
        checkProxy->setChecked(i);
        proxyEnabled = i;

}
bool Proprieta::proxyEn()
{
    return proxyEnabled;
}

void Proprieta::setNumOfDecimals(int i)
{
    if (i<=8 && i>=0)
    numOfDec = i;
    //qDebug()<<"PROP numOfDecimals"<<numOfDec;
}
void Proprieta::updateNumOfDecimals()
{
    sNumOfDecimals->setValue(numOfDec);
}

void Proprieta::updateLang(int i)
{
	if (i==0)
	language = "italiano";
	if (i==1)
	language = "english";
}

int Proprieta::getLang()
{
	return comboLang->currentIndex();
}
void Proprieta::setLanguage(int i)
{
	if ((i>=0) & (i<=1)){
        updateLang(i);
	comboLang->setCurrentIndex(i);
	}
}
Proprieta::~Proprieta()
{
}
int Proprieta::getNumberOfDecimals()
{
    return numOfDec;
}
