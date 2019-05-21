#include <QtGui>

#include "buttonFade.h"
FaderWidget::FaderWidget(QWidget *parent)
: QWidget(parent)
{
  if (parent)
  startBrush = parent->palette().window();
  else
startBrush = Qt::white;

    currentAlpha = 0;
    duration = 32;

    timeLine = new QTimer(this);
    connect(timeLine, SIGNAL(timeout()), this, SLOT(update()));

// qDebug()<<"BF init";
// timeLine = new QTimeLine(2000, this);
// timeLine->setFrameRange( 333,0);
// connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(update()));

setAttribute(Qt::WA_DeleteOnClose);
resize(parent->size());
}
 

void FaderWidget::start( )
{ 
    currentAlpha = 255;
     timeLine->start(16);
    show();
// qDebug()<<"BF start"<<  currentAlpha<< timeLine->interval(); ;
    

//     show();
}
void FaderWidget::paintEvent(QPaintEvent * /* event */)
{
// qDebug()<<"BF paint"<< currentAlpha<< timeLine->interval(); 
    QPainter painter(this);
    QColor semiTransparentColor = startColor;
    semiTransparentColor.setAlpha(currentAlpha);
    painter.fillRect(rect(), semiTransparentColor);

    currentAlpha -= 255 * timeLine->interval() / duration;
    if (currentAlpha <=0) {
        timeLine->stop();
         close();
    }

 
 
}
 
 
// QSize FaderWidget::minimumSizeHint() const
//  {
//        return QSize(120, 180);
//  }