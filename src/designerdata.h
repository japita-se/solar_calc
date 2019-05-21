#ifndef DESIGNERDATA_H
#define DESIGNERDATA_H
#include "ui_designerForm.h"
#include <QWidget>
#include "data.h"
class DesignerData : public QWidget, public Ui::formDesigner
{
Q_OBJECT
public:
    explicit DesignerData(QWidget *parent = 0);


    void setAll(designer d);
    QString getLogoPath();
    QString getDesignerName( );
    QString getReviewerName( );
    QDate getDate( );
    QString getClientName( );
    QString getClientAddress( );
    QString getTitle( );
    QString getNotes( );
    designer getAll();


signals:
    void isDirty();

public slots:
    void setLogoPath(QString a);
    void setDesignerName(  QString a);
    void setReviewerName(  QString a);
    void setDate(  QDate a);
    void setClientName( QString a);
    void setClientAddress(  QString a);
    void setTitle(  QString a);
    void setNotes(  );
    void setAlbo(  QString a);
    void setCompany(  QString a);
private:
    void updateAll();
private:
    designer d;
    bool doNotUpdate;
private slots:
    void loadLogo();
private:
    QString recentDir;


};

#endif // DESIGNERDATA_H
