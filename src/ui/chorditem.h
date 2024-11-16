#ifndef CHORDITEM_H
#define CHORDITEM_H

#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QVariant>
#include "qgraphicsitem.h"
#include "qgraphicssceneevent.h"
#include "qtmetamacros.h"
#include "src/charts/workingchord.h"

class ChordItem : public QObject, public QGraphicsSimpleTextItem {
    Q_OBJECT
public:
    ChordItem(const WorkingChord &chord,
              size_t id,
              size_t measure,
              size_t beat,
              QObject *parent = nullptr);

    ChordItem(const QString &str, size_t id, size_t measure, size_t beat, QObject *parent = nullptr);

    size_t id() const { return m_id; }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
signals:
    void itemSelected(void);

private:
    void init();
    QString m_rootstr, m_extstr, m_bassstr;
    size_t m_id, m_measure, m_beat;
    Q_PROPERTY(size_t id READ id FINAL CONSTANT)
};

#endif // CHORDITEM_H
