#ifndef QINTERVAEDITOR_H
#define QINTERVAEDITOR_H
#include <QPolygonF>
#include <QDialog>
class QTableWidget;
class QTableWidgetItem;
class QPushButton;

class IntervalEditor : public QDialog {

        Q_OBJECT
public:
        IntervalEditor(QWidget* parent=0);
        void setInterval(const QPolygonF &p);
        void resetTable();
        QPolygonF getInterval();
        void setTitle(const QString &t);
        void setLabels(const QStringList &a);
        void setMax(double max);


signals:
        void intervalChanged();
        void tableResetted();
private slots:
        void delRow();
        void clearTable();
        void updateInterval();
        void addRow();
        void addRow(int i);
        void updateExt();
        void updateAndExit();
        void update(QTableWidgetItem* item);
private:
        void printError(int i);
private:
        double max;
        QStringList labels;
        QPolygonF interval;
        QTableWidget* tableWidget;
        QPushButton *delRowButton,*okButton,*applyButton,*cancelButton,*addRowButton,*delButton;
};
#endif // QINTERVAEDITOR_H
