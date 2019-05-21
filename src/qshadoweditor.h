#ifndef QSHADOWEDITOR_H
#define QSHADOWEDITOR_H
#include <QPolygonF>
#include <QDialog>
class QTableWidget;
class QTableWidgetItem;
class QPushButton;

class QShadowEditor : public QDialog {

	Q_OBJECT
public:
	QShadowEditor(QWidget* parent=0);
	void setShadow(const QPolygonF &p);
	void resetTable();
	QPolygonF getShadow();
	
	
signals:
	void shadowChanged();
	void tableResetted();
private slots:
	void delRow();
	void clearTable();
	void updateShadow();
	void addRow();
	void addRow(int i);
	void updateExt();
	void updateAndExit();
	void update(QTableWidgetItem* item);
private:
	QStringList labels;
	QPolygonF shadow;
	QTableWidget* tableWidget;
	QPushButton *delRowButton,*okButton,*applyButton,*cancelButton,*addRowButton,*delButton;
};
#endif
