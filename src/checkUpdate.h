#ifndef _CHECKUPDATE_UI
#define _CHECKUPDATE_UI

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QUrl>
#include <QFile>
#include "ui_checkupdated.h"

class QHttp;

class CheckUpdate : public QDialog, public Ui::CheckUpdate
{
	Q_OBJECT
QNetworkAccessManager manager;

public:
                CheckUpdate(QWidget* parent=0);
                void setUpdateAtStart(bool a);
                bool getUpdateAtStart();
		void setVersion(const QString &a);
// 		bool getFile(const QUrl &url);
		bool newVersion();
		bool getStatus();
		void setUrl(const QUrl& q);
		void doDownload(const QUrl &url);

signals:
                void done(bool a);

private slots:
// 		void httpDone(int i,bool error);
                void updateStart(int i);
		QString saveFileName(const QUrl &url);
		bool saveToDisk(const QString &filename, QIODevice *data);
		void downloadFinished(QNetworkReply *reply);
		void checkVersion(QString& a);

private:
	QHttp* http;
	QFile file;
	QUrl url;
        bool status,newV,atStart;
	QString currentVersion,baseName;
	
};
#endif
