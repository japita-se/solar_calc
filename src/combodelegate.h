#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QItemDelegate>
class ComboDelegate : public QItemDelegate
 {
     Q_OBJECT

 public:
     ComboDelegate(QVector<int> column, QStringList a, QObject *parent = 0);

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
      QStringList items;
      QVector<int> columns;
 };

#endif // COMBODELEGATE_H
