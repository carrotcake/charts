#ifndef CHORDITEM_H
#define CHORDITEM_H

#include <QGraphicsSimpleTextItem>

class ChordItem : public QGraphicsSimpleTextItem {
public:
    ChordItem(const QString& str, QPoint coords);

private:
};

#endif // CHORDITEM_H
