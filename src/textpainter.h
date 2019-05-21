#ifndef TEXTPAINTER_H
#define TEXTPAINTER_H

#include <QMetaType>
#include <QString>

class TextPainter
{
        public:
                enum EditMode { Editable, ReadOnly };

                TextPainter(QString text = "");

                void paint(QPainter *painter, const QStyleOptionViewItem &option, EditMode mode) const;
                QSize sizeHint() const;

        private:

                QString itemText;
};

Q_DECLARE_METATYPE(TextPainter)

#endif
