#include "chorditem.h"
#include <QCursor>
#include <QFont>
#include <QGraphicsSceneHoverEvent>
#include "chartscene.h"
#include "qgraphicsitem.h"
#include "qnamespace.h"

ChordItem::ChordItem(const QString &str, size_t id, size_t measure, size_t beat, QObject *parent)
    : QObject{parent}
    , m_id(id)
    , m_measure(measure)
    , m_beat(beat)
    , m_pen(Qt::black) {
    const auto margin = ChartScene::MARGIN, width = ChartScene::CELLW, height = ChartScene::CELLH,
               offset = ChartScene::VERTOFFSET;
    auto xIdx = measure % 4, yIdx = measure / 4;
    QFont f;
    QPoint coords;
    coords.setX(xIdx * width + beat * (width / 4) + margin);
    coords.setY(yIdx * height + margin + yIdx * offset);
    f.setPointSize(20);
    setText(str);
    setFont(f);
    coords.ry() += 16;
    coords.rx() += 4;
    setPos(coords);
    setCursor(Qt::CursorShape::PointingHandCursor);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    setAcceptHoverEvents(true);
}

void ChordItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    setBrush(Qt::darkGray);
    QGraphicsSimpleTextItem::hoverEnterEvent(event);
}

void ChordItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    if (!isSelected())
        setBrush(Qt::black);
    QGraphicsSimpleTextItem::hoverLeaveEvent(event);
}

QVariant ChordItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemSelectedChange && scene()) {
        if (value == true) {
            setBrush(Qt::darkCyan);
            emit itemSelected();
        } else {
            setBrush(Qt::black);
        }
    }
    return QGraphicsSimpleTextItem::itemChange(change, value);
}
