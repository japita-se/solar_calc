#include "checkUpdate.h"

#include<iostream>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QtNetwork>
using namespace std;
CheckUpdate::CheckUpdate(QWidget* parent) : QDialog(parent) {

	http = new QHttp(this);
        newV = false; // At the start, we suppose that the newVersion is not available
        atStart = false;
	currentVersion="";
	setupUi(this);
// 	connect(http,SIGNAL(requestFinished(int,bool)),SLOT(httpDone(int,bool)));
	connect(pushOK,SIGNAL(clicked()),SLOT(accept()));
        //connect(pushCancel,SIGNAL(clicked()),SLOT(reject()));
        connect(checkStart,SIGNAL(stateChanged(int)),SLOT(updateStart(int)));
         connect(&manager, SIGNAL(finished(QNetworkReply*)),SLOT(downloadFinished(QNetworkReply*)));

	status = false;
	pushOK->setVisible(false);
}
void CheckUpdate::setVersion(const QString &a)
{
	currentVersion = a;
}
void CheckUpdate::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    labelTop->setText("");
    if (reply->error()) {
//         qDebug()<<"Download of  failed: "<<
//                 url.toEncoded().constData()<<qPrintable(reply->errorString());
  		labelUpdate->setText(tr("<p>Problema di connession al server</p>"));
	 qDebug()<<"Download of  failed: ";
                
    } else {
        QString filename = saveFileName(url);
        if (saveToDisk(filename, reply)){
//             printf("Download succeded (saved to %s)\n",
//                    url.toEncoded().constData(), qPrintable(filename));
	 pushOK->setVisible(true);
    checkVersion(filename);
    }
    }
    emit done(newV);
    reply->deleteLater();
       
}
QString CheckUpdate::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QCoreApplication::applicationDirPath() + "/" + QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, remove
        QFile f(basename);
	f.remove();
        
    }

    return basename;
}

bool CheckUpdate::saveToDisk(const QString &filename, QIODevice *data)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
       qDebug()<<"Could not open %s for writing: "<<
                qPrintable(filename)<<
                qPrintable(file.errorString());
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}

// void CheckUpdate::httpDone(int i,bool error)
// {
// 	if (error)
// 	{
// 		status = false;
// 		qDebug()<<"Error in checking updates:"<<qPrintable(http->errorString())<<"\n";
// 		QMessageBox::warning(this,tr("Aggiornamenti"),tr("Errore di connessione...")+http->errorString(),QMessageBox::Ok);
// 	}
// 	else
// 	{
// 	status = true;
// 	qDebug()<<"No Error in checking updates:";
// 	pushOK->setVisible(true);
// 	file.close();
// 	checkVersion(file);
// 	 
// 	
// 	}
// 	
// 	
// 	
// }
void CheckUpdate::checkVersion( QString &filename)
{
	QString version;	
	QFile f(filename);
	if (!f.open(QIODevice::ReadOnly))
		qDebug()<<"SOME ERROR IN CHECKING VERSION UPDATES";
	else{
		QTextStream in(&f);
                /* FOR NOW WE LET TO CHECK ONLY ONE INFORMATION: the VersionId*/
                while (!in.atEnd()){
			version  =in.readLine();
                        break;
                    }



	if (version != currentVersion){
			newV = true;
			labelUpdate->setText(tr("<p><h4> Una nuova versione &egrave; disponibile sul sito! </h4><p>Version Id:") + version + tr("<p> Per scaricare la nuova versione accedi a <a href=\"http://www.studioiacovoni.org\"> studioiacovoni.org</a></p>"));
                        qDebug()<<"NUOVA VERSIONE"<<version<<currentVersion;
	}
	else{
			newV = false;
			labelUpdate->setText(tr("<p>La versione che stai usando &egrave; la pi&ugrave; aggiornata</p>"));
			qDebug()<<"VECCHIA o AGGIORNATA VERSIONE";
	}
	


}
}
bool CheckUpdate::newVersion()
{
	return newV;
}
bool CheckUpdate::getStatus( )
{
	return status;
}

void CheckUpdate::doDownload(const QUrl &url)
{
    labelTop->setText(tr("Attendere"));
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

     
}

// bool CheckUpdate::getFile(const QUrl &url)
// {
// 	
// 	if (!url.isValid()) {
// 		qDebug()<<"CU no url valid"<<url;
// 		return false;
// 	}
// 	if (url.scheme() != "http"){
// 		qDebug()<<"CU url must start with http"<<url;
// 		return false;
// 	}
// 	if (url.path().isEmpty()){
// 		qDebug()<<"CU url path is empty"<<url;
// 		return false;
// 	}
// 	QString localFileName =  QFileInfo(url.path()).fileName();
// 	if (localFileName.isEmpty())
// 		localFileName = "httget.out";
// 	file.setFileName(localFileName);
// 	if (!file.open(QIODevice::WriteOnly)){
// 		cerr << "Error in CU: cannot open "<<qPrintable(file.fileName());
// 		return false;
// 	}
// 
// 
//  http->setHost(url.host(),QHttp::ConnectionModeHttp,url.port());
// int getId = http->get( QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/"),&file);
// qDebug()<<"CU url"<<url.host()<<url.path();
// qDebug()<<"CU getId"<<getId;
// 
// // return true;
// }
void CheckUpdate::setUrl(const QUrl &u)
{
	url = u;
}
void CheckUpdate::setUpdateAtStart(bool a)
{
    atStart = a;
    checkStart->setChecked(a);
}

void CheckUpdate::updateStart(int i)
{
    if (i==Qt::Checked)
        atStart = true;
    else
        atStart = false;
}

bool CheckUpdate::getUpdateAtStart()
{
    return atStart;
}
