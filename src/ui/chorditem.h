#ifndef CHORDITEM_H
#define CHORDITEM_H

#include <QGraphicsSimpleTextItem>

class ChordItem : public QGraphicsSimpleTextItem {
public:
    ChordItem(const QString& str, size_t id, size_t measure, size_t beat);

private:
    size_t m_id, m_measure, m_beat;
};

#endif // CHORDITEM_H
