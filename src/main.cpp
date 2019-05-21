/***************************************************************************
 *   Copyright (C) 2008/2010 by giuseppe   *
 *   giuseppe@localhost.localdomain   *
 *                                                                         *
 *  StudioIacovoni.org
 ***************************************************************************/
#define WITHTOOLS
#define PLUSVERSION
#include <QtGui>
#include "shoemessage.h"
// #include "myplot.h"
#include "mainwindow.h"
#include "chooselang.h"
#include <QApplication>
#include <QSplashScreen>
#include <QNetworkInterface>
#include <QUrl>
/* SHADOWING OF CODE */
static QString lokinju="hdfawi28947sd83hcnbwghfHJu2337JHwqaL";
static QString m3link = QString("ioeks902");
#define neutral_mask 0
#define timerset 1200
static QString solk="/linux";
static QString a1= "w";
static QString a22= "204985d";
static QString a2= "w";
static QString a223= "204985d";
static QString a4= "w";
#define ESCALATOR_5 5
static QString bc22= "st";
static QString bc23= "org";
static QString bc24= "dio";
static QString bc25= "u";
static QString bc2292= "stele";
static QString bc26= "vo";
static QString bc27= "ni";
static QString bc229= "204985d";
static QString bc28= "iac";
static QString bc29= "o";

#ifdef PLUSVERSION
static QString version = "3 Plus";
	#ifdef Q_OS_LINUX
	static QUrl urlOwner(QUrl::fromEncoded(QString("http://" + a1 + a2 + a4 + "."  + bc22 + bc25 + bc24 +bc28 + bc29+bc26+bc27 +".org" + "/" + lokinju + solk+ "/versionplus.txt").toLocal8Bit() ));
	#endif
	#ifdef Q_OS_WIN32
	static QUrl urlOwner(QUrl::fromEncoded(QString("http://" + a1 + a2 + a4 + "."  + bc22 + bc25 + bc24 +bc28 + bc29+bc26+bc27 +".org" + "/" + lokinju + "/versionplus.txt").toLocal8Bit() ));
	#endif
#else
	static QString version = "3 Community Edition";
	#ifdef Q_OS_LINUX
	static QUrl urlOwner(QUrl::fromEncoded(QString("http://" + a1 + a2 + a4 + "."  + bc22 + bc25 + bc24 +bc28 + bc29+bc26+bc27 +".org" + "/" + lokinju +  solk + "/version.txt").toLocal8Bit() ));
	#endif
	#ifdef Q_OS_WIN32
	static QUrl urlOwner(QUrl::fromEncoded(QString("http://" + a1 + a2 + a4 + "."  + bc22 + bc25 + bc24 +bc28 + bc29+bc26+bc27 +".org" + "/" + lokinju + "/version.txt").toLocal8Bit() ));
	#endif
#endif

/*TESTEST*/
static double x = 0;
static QString versionId = "20130408.00.00";
#ifdef PLUSVERSION
static QStringList allowed = QStringList() <<"00:24:A5:49:B2:3F"
                                           <<"00:26:9E:7C:14:61"
                                           <<"00-26-9E-7C-14-61";;

#endif

 void myMessageOutput(QtMsgType type, const char *msg)
 {
     switch (type) {
     case QtDebugMsg:
         fprintf(stderr, "Debug: %s\n", msg);
         break;
     case QtWarningMsg:
//          fprintf(stderr, "Warning: %s\n", msg);
         break;
     case QtCriticalMsg:
         fprintf(stderr, "Critical: %s\n", msg);
         break;
     case QtFatalMsg:
         fprintf(stderr, "Fatal: %s\n", msg);
         abort();
     }
 }

    int main( int argc, char **argv )
{


    //FOR PRODUCTION DO NOT DELETE THE FOLLOWING LINE //
     qInstallMsgHandler(myMessageOutput);





QCoreApplication::setOrganizationName("StudioIacovoni.org");
QCoreApplication::setApplicationName("SolarCalc " + version);
Q_INIT_RESOURCE(resource);
 
QTranslator appTranslator;
 

  QSettings settings;
  QString la,loadProject;
  QFileInfo filePath;
  QFile f;

  int lang_id=0;
  if (argc==2){
      QStringList arguments;

      for(int i=1;i<argc;i++)
          arguments<<argv[i];
      f.setFileName(arguments.at(0));
      if (f.exists()){
          loadProject = QFileInfo(f).absoluteFilePath();
         // qDebug()<<"MAIN LOADPROJECT FROM FILE"<<loadProject;
      }
   }


QApplication a( argc, argv );
#ifdef PLUSVERSION
#ifdef TESTER
/**********CHECK THE MAC ADDRESS *******************************/
        QNetworkInterface ifi;
        QStringList hardwareNI;
        QString temp;
        bool    go = false;
        int     k  = 0;
//        qDebug()<<"MAIN MAC"<<ifi.hardwareAddress();
        for (int i=0;i<ifi.allInterfaces().size();i++){
            temp = ifi.allInterfaces().at(i).hardwareAddress();
            if (!hardwareNI.contains(temp) && temp!="00:00:00:00:00:00:00:E0"){

                   hardwareNI << temp;
                  // qDebug() << hardwareNI << i;
                   if (allowed.contains(hardwareNI.at(k)))
                       go = true;
                    k++;
               }
        }
         if (!go)
        {
            ShowMessage ws;
            ws.setMessage(QObject::tr("<p>Errore. Questa &egrave; una versione di test che non pu&ograve; essere usata su questa macchina. </p>"));
            ws.showMessage();
             exit(1);
        }
#endif
#endif

QSplashScreen pSplash(QPixmap(":/splash/interfaccia2.jpg"), Qt::WindowStaysOnTopHint);
  
  
  
#ifndef PLUSVERSION
  if (!settings.contains("setup")) {
        /* It means that this is the first time we use the progrma */
        ChooseLang ch(new QWidget(),0);
        //ch.label_2->setPixmap(QPixmap(":/images/logo.png"));

        if (ch.exec()) {
                lang_id = ch.getLang();
                if (lang_id ==1)
                        {
                        la ="en";
                        appTranslator.load("solarcalc_"+la,":/translations");
                        }
        settings.setValue("setup",1);
        }
        else
        {
                lang_id=0;
                settings.setValue("setup",1);
        }
  }
  else
         if (settings.contains("lang")) {
                if (settings.value("lang").toInt()==1)
                {
                la ="en";
                lang_id=1;
                appTranslator.load("solarcalc_"+la,":/translations");
                }
        } else
                {

                lang_id = 0;
                qDebug()<<"MAIN, no lang tag"<<lang_id<<settings.value("lang").toInt()<<settings.contains("lang");
                }
#endif

#ifdef PLUSVERSION
        /*SET ONLY ITALIAN*/
        lang_id=0;
        settings.setValue("setup",1);
        /*******************/
#endif
   a.installTranslator(&appTranslator);

   a.processEvents();
   pSplash.show();	
   pSplash.raise();
   pSplash.showMessage("<br><font color=\"white\">" + QObject::tr("Carico dati...") + "</font>");
   MainWindow mainWindow;
   mainWindow.setVersion(version,versionId,urlOwner);
   mainWindow.setLang(lang_id);	
   #ifdef WITHTOOLS
//	QProgressBar p(&pSplash);
//
//// 	p.setGeometry(pSplash.geometry().x(),pSplash.geometry().y(),pSplash.width(),500 );
//	p.setGeometry(0,0,pSplash.width(),20 );
//	p.show();
//        p.setMaximum(60000*3);
//	p.setMinimum(0);
//	qDebug()<<"Start Inserting NasaRad...";
//         mainWindow.prepareNasaRad(p,0);
//	qDebug()<<"Start Inserting NasaTemp...";
//        mainWindow.prepareNasaTemp(p,65000);
////	qDebug()<<"Start Inserting NasaWind...";
//         mainWindow.prepareNasaWind(p,65000*2);
	#endif
//    mainWindow.show();
   pSplash.finish(&mainWindow);
   
   
    mainWindow.show();
  	
  
  
    pSplash.showMessage("<font color=\"white\">" + QObject::tr("Interfaccia pronta") + "</font>");
 if (!loadProject.isEmpty())
     mainWindow.load(loadProject);

    
//     connect(a,SIGNAL(aboutToQuit()),SLOT(cleanUp()));
    
   
//   a.setMainWidget(sw);
  return a.exec();
}  

// void aboutToQuit()
// {
// 	delete mainWindow;
// }
