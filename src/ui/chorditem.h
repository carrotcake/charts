#ifndef CHORDITEM_H
#define CHORDITEM_H

#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QVariant>
#include "qgraphicsitem.h"
#include "qtmetamacros.h"

class ChordItem : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
public:
    ChordItem(const QString &str, size_t id, size_t measure, size_t beat, QObject *parent = nullptr);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
signals:
    void itemSelected(void);

private:
    size_t m_id, m_measure, m_beat;
    QPen m_pen;
};

#endif // CHORDITEM_H
