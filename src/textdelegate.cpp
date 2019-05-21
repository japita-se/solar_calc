#include <QtGui>

#include "textdelegate.h"
#include "textpainter.h"

void TextDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
        if (qVariantCanConvert<TextPainter>(index.data())) {
                TextPainter textPainter = qVariantValue<TextPainter>(index.data());

                if (option.state & QStyle::State_Selected)
                        painter->fillRect(option.rect, option.palette.highlight());

                textPainter.paint(painter, option, TextPainter::ReadOnly);
        } else {
                QItemDelegate::paint(painter, option, index);
        }
}

QSize TextDelegate::sizeHint(const QStyleOptionViewItem &option,
                                                         const QModelIndex &index) const
{
        if (qVariantCanConvert<TextPainter>(index.data())) {
                TextPainter textPainter = qVariantValue<TextPainter>(index.data());
                return textPainter.sizeHint();
        } else {
                return QItemDelegate::sizeHint(option, index);
        }
}
