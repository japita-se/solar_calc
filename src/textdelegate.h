#ifndef TEXTDELEGATE_H
#define TEXTDELEGATE_H

#include <QItemDelegate>

class TextDelegate : public QItemDelegate
{
        Q_OBJECT

        public:
                TextDelegate(QWidget *parent = 0) : QItemDelegate(parent) {}

                void paint(QPainter *painter, const QStyleOptionViewItem &option,
                                   const QModelIndex &index) const;
                QSize sizeHint(const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const;
};

#endif
