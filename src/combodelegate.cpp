#include "combodelegate.h"
#include <QComboBox>
#include <QtGui>
ComboDelegate::ComboDelegate( QVector<int> c, QStringList  a ,QObject*parent):QItemDelegate(parent)
{
        this->items  = a;
        this->columns = c;
}

QWidget *ComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & option ,    const QModelIndex &index) const
 {
     if (columns.contains(index.column())) {
        //qDebug()<<"DD out"<<index.column();
     QComboBox *editor = new QComboBox(parent);
     editor->addItems(items);



     return editor;
        }else {
        return QItemDelegate::createEditor(parent, option, index);
}
 }

void ComboDelegate::setEditorData(QWidget* editor,const QModelIndex &index) const
{
        if (columns.contains(index.column())) {
        QString d = index.model()->data(index,Qt::EditRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);

        comboBox->setCurrentIndex(comboBox->findText(d));
    } else {
        QItemDelegate::setEditorData(editor, index);

}
}
void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
 {
    if (columns.contains(index.column())) {
     QComboBox *comboBox = qobject_cast<QComboBox*>(editor);

     QString value = comboBox->currentText();

     model->setData(index, value);
 } else {
        QItemDelegate::setModelData(editor,model,index);
}
}
void ComboDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
 }

void ComboDelegate::commitAndCloseEditor()
{
        QComboBox *editor = static_cast<QComboBox *>(sender());
        emit commitData(editor);
        emit closeEditor(editor);
}


