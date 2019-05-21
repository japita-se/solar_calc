#ifndef REALEDELEGATE_
#define REALEDELEGATE_
#include <QItemDelegate>
class RealeDelegate : public QItemDelegate
 {
     Q_OBJECT

 public:
     RealeDelegate(QVector<int> co, QObject *parent = 0);

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
        int column;
 };
#endif