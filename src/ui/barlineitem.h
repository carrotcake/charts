#ifndef BARLINEITEM_H
#define BARLINEITEM_H
#include <QGraphicsLineItem>

class BarlineItem : public QGraphicsLineItem {
public:
    BarlineItem(size_t id, size_t measure);

private:
    size_t m_id, m_measure;
};

#endif // BARLINEITEM_H
