#ifndef FADERWIDGET_H
#define FADERWIDGET_H

#include <QWidget>
#include <QPushButton>
class QTime ;

class FaderWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor fadeColor READ fadeColor WRITE setFadeColor)
    Q_PROPERTY(int fadeDuration READ fadeDuration WRITE setFadeDuration)
public:

    FaderWidget(QWidget *parent);

    QColor fadeColor() const { return startColor; }
    void setFadeColor(const QColor &newColor) { startColor = newColor; }

    int fadeDuration() const { return duration; }
    void setFadeDuration(int milliseconds) { duration = milliseconds; }

   
public slots:
  void start( );
protected:
    void paintEvent(QPaintEvent *event);
 
private:
	QBrush startBrush;
	
	QTimer  *timeLine;
 
    QColor startColor;
    
    int duration;
	double  currentAlpha;
};

#endif
 