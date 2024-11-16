#ifndef LABELITEM_H
#define LABELITEM_H

#include <QGraphicsSimpleTextItem>

class LabelItem : public QGraphicsSimpleTextItem {
public:
    LabelItem(const QString &str, size_t id, size_t measure);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    size_t m_id, m_measure;
};

#endif // LABELITEM_H
