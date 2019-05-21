#include "doubledelegate.h"
#include <QDoubleSpinBox>
#include <QtGui>
DoubleDelegate::DoubleDelegate(QVector<int> cols,double upperLimit,double lowerLimit,double decimals,QObject*parent):QItemDelegate(parent)
{
	this->columns=cols;
	this->upper = upperLimit;
	this->lower = lowerLimit;
	this->decimals = decimals;
}

QWidget *DoubleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & option ,    const QModelIndex &index) const
 {
     if (columns.contains(index.column())) {
        //qDebug()<<"DD out"<<index.column();
     QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
     editor->setMinimum(lower);
     editor->setMaximum(upper);
     editor->setDecimals(decimals);

     return editor;
	}else {
	return QItemDelegate::createEditor(parent, option, index);
}
 }

void DoubleDelegate::setEditorData(QWidget* editor,const QModelIndex &index) const
{
        if (columns.contains(index.column())) {
        double d = index.model()->data(index,Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);

        spinBox->setValue(d);
    } else {
        QItemDelegate::setEditorData(editor, index);

}
}
void DoubleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
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
void DoubleDelegate::updateEditorGeometry(QWidget *editor,
     const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
 {
     editor->setGeometry(option.rect);
 }

void DoubleDelegate::commitAndCloseEditor()
{
        QDoubleSpinBox *editor = static_cast<QDoubleSpinBox *>(sender());
        emit commitData(editor);
        emit closeEditor(editor);
}

