#include "doubledelegate.h"
#include <QDoubleSpinBox>
#include <QtGui>
RealeDelegate::RealeDelegate(int col,QObject*parent):QItemDelegate(parent)
{
	this->column=col;
}

QWidget *RealeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & option ,    const QModelIndex &index) const
 {
     if (column.contains(index.column())) {
     QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
     editor->setMinimum(0);
     editor->setMaximum(100);
     editor->setDecimals(3);

     return editor;
	}else {
	return QItemDelegate::createEditor(parent, option, index);
}
 }

void RealeDelegate::setEditorData(QWidget* editor,const QModelIndex &index) const
{
        if (columns.contains(index.column())) {
        double d = index.model()->data(index,Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);

        spinBox->setValue(d);
    } else {
        QItemDelegate::setEditorData(editor, index);

}
}
void RealeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
 {
    if (columns.contains(index.column())) {
     QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(editor);
     spinBox->interpretText();
     double value = spinBox->value();

     model->setData(index, value);
 } else {	
	QItemDelegate::setModelData(editor,model,index);
}
}
void RealeDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
 }

void RealeDelegate::commitAndCloseEditor()
{
        QDoubleSpinBox *editor = static_cast<QDoubleSpinBox *>(sender());
        emit commitData(editor);
        emit closeEditor(editor);
}

