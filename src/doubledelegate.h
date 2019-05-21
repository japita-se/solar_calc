#ifndef DOUBLEDELEGATE_
#define DOUBLEDELEGATE_
#include <QItemDelegate>
class DoubleDelegate : public QItemDelegate
 {
     Q_OBJECT

 public:
     DoubleDelegate(QVector<int> co, double u, double l,double decimals,QObject *parent = 0);

     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                       const QModelIndex &index) const;

     void updateEditorGeometry(QWidget *editor,
         const QStyleOptionViewItem &option, const QModelIndex &index) const;
private slots:
        void commitAndCloseEditor();
private:
        QVector<int> columns;
	double upper;
	double lower;
	double decimals;
 };
#endif