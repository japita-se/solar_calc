#ifndef MYFILTER_H
#define MYFILTER_H


 #include <QDate>
 #include <QSortFilterProxyModel>

 class MyFilterProxyModel : public QSortFilterProxyModel
 {
     Q_OBJECT

 public:
     MyFilterProxyModel(QObject *parent = 0);

     void setSourceCol(int col0,int col1);
     void setSourceString(const QString &a);

 protected:
     bool filterAcceptsRow(int sourceRow,  const QModelIndex &sourceParent) const;


 private:
     int sourceCol0,sourceCol1;
     QString sourceString;



 };


#endif // MYFILTER_H
