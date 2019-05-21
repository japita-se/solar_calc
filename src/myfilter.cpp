#include <QtGui>

 #include "myfilter.h"

 MyFilterProxyModel::MyFilterProxyModel(QObject *parent)
     : QSortFilterProxyModel(parent)
 {
     sourceString = "";
     sourceCol0 = sourceCol1 = 0;
     invalidateFilter();

 }


 void MyFilterProxyModel::setSourceCol(int col0,int col1){
     sourceCol0 = col0;// the column for the regexp
     sourceCol1 = col1;// the column for the fixed string (costruttore)
     invalidateFilter();
 }


 void MyFilterProxyModel::setSourceString(const QString &a){
     sourceString = a;
 }

 bool MyFilterProxyModel::filterAcceptsRow(int sourceRow,
         const QModelIndex &sourceParent) const
 {

     QModelIndex index0 = sourceModel()->index(sourceRow, sourceCol0, sourceParent);
     QModelIndex index1 = sourceModel()->index(sourceRow, sourceCol1, sourceParent);


     return (sourceModel()->data(index0).toString().contains(filterRegExp())
             && sourceModel()->data(index1).toString().contains(sourceString));

 }



