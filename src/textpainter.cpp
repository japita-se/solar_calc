#include <QtGui>

#include "textpainter.h"

const int PaintingScaleFactor = 20;

TextPainter::TextPainter(QString text)
{
        itemText = text;
}

QSize TextPainter::sizeHint() const
{
        return PaintingScaleFactor * QSize(itemText.length()/2-2, 1);
}

void TextPainter::paint(QPainter *painter, const QStyleOptionViewItem &option, EditMode mode) const
{
        if (mode == Editable) {
                painter->setBrush(option.palette.highlight());
        } else {
                painter->setBrush(option.palette.foreground());
        }

        qDebug()<<"TP HEI";
        painter->save();
        QTextDocument doc;
        doc.setHtml(itemText);
        QAbstractTextDocumentLayout::PaintContext context;
        doc.setPageSize( option.rect.size());
        painter->translate(option.rect.x(), option.rect.y()-20);
        doc.documentLayout()->draw(painter, context);
        painter->restore();
}
