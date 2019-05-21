#include "designerdata.h"

DesignerData::DesignerData(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    doNotUpdate = false;
    recentDir = QDir::homePath();
    dateEdit->setDate(QDate::currentDate());


    connect(lineName,SIGNAL(textChanged(QString)),SLOT(setDesignerName(QString)));

    connect(lineClientAddress,SIGNAL(textChanged(QString)),SLOT(setClientAddress(QString)));
    connect(lineReviewer,SIGNAL(textChanged(QString)),SLOT(setReviewerName(QString)));

    connect(lineAlbo,SIGNAL(textChanged(QString)),SLOT(setAlbo(QString)));

    connect(lineCompany,SIGNAL(textChanged(QString)),SLOT(setCompany(QString)));

    connect(lineClient,SIGNAL(textChanged(QString)),SLOT(setClientName(QString)));

    connect(dateEdit,SIGNAL(dateChanged(QDate)),SLOT(setDate                           (QDate)));

    connect(textNotes,SIGNAL(textChanged()),SLOT(setNotes()));

    connect(lineTitle,SIGNAL(textChanged(QString)),SLOT(setTitle(QString)));

    connect(lineLogo,SIGNAL(textChanged(QString)),SLOT(setLogoPath(QString)));
    connect(pushLogo,SIGNAL(clicked()),SLOT(loadLogo()));


}

void DesignerData::setDesignerName( QString a)
{

    if (!doNotUpdate){

    d.name = a;

}
}

void DesignerData::setReviewerName(  QString a)
{
    if (!doNotUpdate){
    d.name_r = a;
    emit isDirty();
}
}

void DesignerData::setDate(  QDate a)
{
    if (!doNotUpdate){
    d.date = a;
    emit isDirty();
}
}

void DesignerData::setClientName(  QString a)
{
    if (!doNotUpdate){
    d.clientName = a;
    emit isDirty();
}
}
void DesignerData::setCompany(  QString a)
{
    if (!doNotUpdate){
    d.company = a;
    emit isDirty();
}
}

void DesignerData::setAlbo(  QString a)
{
    if (!doNotUpdate){
    d.albo = a;
    emit isDirty();
}
}



void DesignerData::setClientAddress(  QString a)
{

    if (!doNotUpdate){
    d.clientAddress  = a;
    emit isDirty();
}
}
void DesignerData::setTitle(  QString a)
{
    if (!doNotUpdate){
    d.title = a;
    emit isDirty();
}
}

void DesignerData::setNotes(   )
{
    if (!doNotUpdate){
    d.notes = textNotes->document()->toHtml();
    emit isDirty();
}
}
void DesignerData::setLogoPath(QString a)
{
    if (!doNotUpdate)

    if (!QFile::exists(a))

        QMessageBox::warning(this,tr("Errore"),tr("Immagine non trovata. Ricontrolla"));
    else
    {
        d.logoPath = a;
        labelLogo->setPixmap(QPixmap(a));
        qDebug()<<"DD immagine settata nella preview"<<a;
    }
    emit isDirty();
}

QString DesignerData::getDesignerName( )
{
    return d.name;
}
QString DesignerData::getLogoPath()
{
       return d.logoPath;
}

QString DesignerData::getReviewerName(  )
{
    return d.name_r;
}

QDate DesignerData::getDate(  )
{
    return d.date;
}

QString DesignerData::getClientName(  )
{
    return d.clientName;
}

QString DesignerData::getClientAddress(   )
{
    return d.clientAddress;
}

QString DesignerData::getTitle( )
{
    return d.title;
}

QString DesignerData::getNotes( )
{
    return d.notes;


}
designer DesignerData::getAll()
{
    qDebug()<<"DD getAll"<<d.logoPath;
    return d;
}



void DesignerData::updateAll()
{

  doNotUpdate = true;
  lineName->setText(d.name);
  lineClientAddress->setText(d.clientAddress);
  lineReviewer->setText(d.name_r);
  lineAlbo->setText(d.albo);
  lineCompany->setText(d.company);
  lineClient->setText(d.clientName);
  dateEdit->setDate(d.date);
  textNotes->setText(d.notes);
  lineTitle->setText(d.title);
  lineLogo->setText(d.logoPath);
  labelLogo->setPixmap(QPixmap(d.logoPath));
  doNotUpdate = false;

}


void DesignerData::setAll(designer de)
{
    d = de;
    updateAll();
    qDebug()<<"DD update";
}
void DesignerData::loadLogo()
{
    QString f = QFileDialog::getOpenFileName(this,tr("Carica logo"),recentDir,tr("Image-Files (*.jpg *.jpeg *.png *.bmp *.gif *.pgm *.ppm *.xpm *.html);;All Files (*)"));

    QFile file(f);
    if (!file.open(QIODevice::ReadOnly ))
    {
        QMessageBox::critical(this,tr("Errore"),tr("Non riesco a leggere il file"));
        return ;
    }
    else
    {
        recentDir = QFileInfo(file).absoluteDir().absolutePath();
        setLogoPath(QFileInfo(file).absoluteFilePath());
        qDebug()<<"DD ho settato il logo"<<d.logoPath;
    }

}
