#include "doubledelegate.h"
#include "qintervaleditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtGui>
#include <QDialog>
IntervalEditor::IntervalEditor(QWidget* parent) : QDialog(parent)
{
        labels<<tr("Da kWh/anno")<<tr("A kWh/anno");
        max = 1000000;
        okButton = new QPushButton(tr("OK"));
        QVBoxLayout* vlayout = new QVBoxLayout;
        QHBoxLayout* layoutButtons = new QHBoxLayout;
        QHBoxLayout* layoutTopButtons = new QHBoxLayout;
        tableWidget = new QTableWidget(2,2,this);
//    	tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->setHorizontalHeaderLabels(labels);
        QVector<int> d;
        d<<0<<1;
        tableWidget->setItemDelegate(new DoubleDelegate(d,max,0,2));

        addRowButton=new QPushButton(tr("&Aggiungi"));
        delRowButton=new QPushButton(tr("&Elimina"));
        applyButton=new QPushButton(tr("Applica"));
       // cancelButton = new QPushButton(tr("Cancella"));
        delButton = new QPushButton(tr("Resetta"));

        connect(okButton,SIGNAL(clicked()),SLOT(updateAndExit()));
        connect(applyButton,SIGNAL(clicked()),SLOT(updateExt()));
     //   connect(cancelButton,SIGNAL(clicked()),SLOT(reject()));
        connect(addRowButton,SIGNAL(clicked()), SLOT(addRow()));
        connect(delRowButton,SIGNAL(clicked()), SLOT(delRow()));
        connect(delButton,SIGNAL(clicked()), SLOT(clearTable()));


        layoutTopButtons->addWidget(addRowButton);
        layoutTopButtons->addWidget(delRowButton);

        layoutButtons->addWidget(okButton);
        layoutButtons->addWidget(applyButton);
        layoutButtons->addWidget(delButton);
     //   layoutButtons->addWidget(cancelButton);

        vlayout->addLayout(layoutTopButtons);
        vlayout->addWidget(tableWidget);
        vlayout->addLayout(layoutButtons);
        setLayout(vlayout);
// 	qDebug()<<tableWidget->rowCount();
// 	tableWidget->setSortingEnabled(false);
        for (int i=0;i<tableWidget->rowCount();i++){
                QTableWidgetItem *item1 = new QTableWidgetItem;
                QTableWidgetItem *item2 = new QTableWidgetItem;
                tableWidget->setItem(i,0,item1);
                tableWidget->setItem(i,1,item2);
                interval<<QPointF(0,0);
        }
// 	tableWidget->setSortingEnabled(true);
// 	connect(tableWidget,SIGNAL(itemChanged( QTableWidgetItem*)),SLOT(update( QTableWidgetItem*)));
       // setWindowTitle(tr("Editor di intervalli di consumo totale"));
}
void IntervalEditor::setTitle(const QString &t)
{
    setWindowTitle(t);
}

void IntervalEditor::addRow()
{

        tableWidget->insertRow(tableWidget->rowCount());
//  	qDebug()<<"QSE rowcount addrow";
        QTableWidgetItem *item1 = new QTableWidgetItem;
        QTableWidgetItem *item2 = new QTableWidgetItem;
        tableWidget->setItem(tableWidget->rowCount()-1,0,item1);
        tableWidget->setItem(tableWidget->rowCount()-1,1,item2);
}
void IntervalEditor::addRow(int num)
{



        for(int i=0;i<num;i++){
                tableWidget->insertRow(tableWidget->rowCount());
                interval<<(QPointF(0,0));
// 		qDebug()<<"QS addrow"<<i;
                QTableWidgetItem *item1 = new QTableWidgetItem;
                QTableWidgetItem *item2 = new QTableWidgetItem;
                tableWidget->setItem(tableWidget->rowCount()-1,0,item1);
                tableWidget->setItem(tableWidget->rowCount()-1,1,item2);
        }
// 	qDebug()<<"QShadow ADDROW"<<tableWidget->rowCount();
}
void IntervalEditor::update(QTableWidgetItem* item)

{

// 	int column = item->column();
//   	if ((column==0) && tableWidget->item(item->row(),1)){
//
//   	shadow.replace(item->row(),QPointF(item->text().toDouble(),tableWidget->item(item->row(),1)->text().toDouble()));
// 	qDebug()<<"QSE item changed"<<item->row()<<tableWidget->item(item->row(),1)->text()<<shadow;
//   	}
//   	if ((column==1) && tableWidget->item(item->row(),0)) {
//  	shadow.replace(item->row(),QPointF(tableWidget->item(item->row(),0)->text().toDouble(),item->text().toDouble()));
// // 	qDebug()<<"QSE item changed"<<item->row()<<tableWidget->item(item->row(),0)->text()<<shadow;
//   	}


}
void IntervalEditor::setInterval(const QPolygonF &p)
{
        interval.resize(0);
        interval=p;
// 	tableWidget->setSortingEnabled(false);
        if (p.size()>tableWidget->rowCount())
                addRow(p.size()-tableWidget->rowCount());
        {
           for(int i=0;i<p.size();i++){
                tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(p.at(i).x())));
                tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(p.at(i).y())));
               // qDebug()<<"Interval "<<p.at(i).x()<<p.at(i).y()<<p.size()<<tableWidget->rowCount();
        }
        }
// 	tableWidget->setSortingEnabled(true);

}
void IntervalEditor::clearTable()
{
// 	qDebug()<<"QSE table resetted";
        tableWidget->clear();
        interval.resize(0);
        tableWidget->setHorizontalHeaderLabels(labels);
        emit tableResetted();
}
void IntervalEditor::resetTable()
{
        for(int i=0;i<tableWidget->rowCount();i++){
                tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(0)));
                tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(0)));
        }
}
void IntervalEditor::updateInterval()
{
    QString da,a;
        interval.resize(0);
        for(int i=0;i<tableWidget->rowCount();i++)
        if (tableWidget->item(i,0) && tableWidget->item(i,1) ){
                da =  tableWidget->item(i,0)->text();
                a  =  tableWidget->item(i,1)->text();

                if (!da.isEmpty() && !a.isEmpty()){
                    if (da.toDouble() <= a.toDouble())
                        interval << QPointF(da.toDouble(),a.toDouble());
                    else{
                        printError(i);
                    }
                }
        }
        qDebug()<<"Interval "<<interval;
}
void IntervalEditor::updateExt()
{

// 	tableWidget->sortItems(0,Qt::AscendingOrder);
        updateInterval();
        emit intervalChanged();
}
void IntervalEditor::updateAndExit()
{
// 	tableWidget->sortItems(0,Qt::AscendingOrder);
        updateInterval();
        accept();
}
QPolygonF IntervalEditor::getInterval()
{
        return interval;
}

void IntervalEditor::delRow()
{

        QList<QTableWidgetSelectionRange> sel = tableWidget->selectedRanges();
        for(int k=0;k<sel.size();k++){
            for(int j=sel.at(k).topRow();j<=sel.at(k).bottomRow();j++)
                for(int m=sel.at(k).leftColumn();m<=sel.at(k).rightColumn();m++){
                    qDebug()<<"Interval delRow"<<m;
                delete tableWidget->item(j,m);
                delete tableWidget->item(j,m);
                }
        }
        updateInterval();
}

void IntervalEditor::printError(int i)
{
    QMessageBox::critical(this,tr("Intervalli di consumo - Errore"),tr("<p>Errore alla riga") + QString::number(i) + ". Il valore DA deve essere minore del valore A.</p>");
}
void IntervalEditor::setLabels(const QStringList &a)
{
    labels.clear();
    labels = a;
    tableWidget->setHorizontalHeaderLabels(labels);
}
void IntervalEditor::setMax(double m)
{
    max = m;
    QVector<int> d;
    d<<0<<1;
    tableWidget->setItemDelegate(new DoubleDelegate(d,max,0,2));
}
