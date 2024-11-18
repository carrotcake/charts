#include "chorditem.h"
#include <QCursor>
#include <QFont>
#include <QGraphicsSceneHoverEvent>
#include "chartscene.h"
#include "qgraphicsitem.h"
#include "qnamespace.h"
#include <algorithm>

void ChordItem::init() {
    const auto margin = ChartScene::MARGIN, width = ChartScene::CELLW, height = ChartScene::CELLH,
               offset = ChartScene::VERTOFFSET;
    auto xIdx = m_measure % 4, yIdx = m_measure / 4;
    QFont f;
    QPoint coords;
    coords.setX(xIdx * width + m_beat * (width / 4) + margin);
    coords.setY(yIdx * height + margin + yIdx * offset);
    f.setPointSize(20);
    setText(m_rootstr);
    setFont(f);
    coords.ry() += 16;
    coords.rx() += 4;
    setPos(coords);
    setCursor(Qt::CursorShape::PointingHandCursor);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    setAcceptHoverEvents(true);
}

ChordItem::ChordItem(
    const WorkingChord &chord, size_t id, size_t measure, size_t beat, QObject *parent)
    : QObject{parent}
    , m_id(id)
    , m_measure(measure)
    , m_beat(beat) {
    m_rootstr = QString::fromStdString(chord.rootStr());
    m_extstr = QString::fromStdString(chord.extStr());
    m_bassstr = QString::fromStdString(chord.bassStr());
    init();
}
ChordItem::ChordItem(const QString &str, size_t id, size_t measure, size_t beat, QObject *parent)
    : QObject{parent}
    , m_id(id)
    , m_measure(measure)
    , m_beat(beat) {
    m_rootstr = str;
    m_extstr = "";
    m_bassstr = "";
    init();
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
        } else {
            setBrush(Qt::black);
        }
    }
    return QGraphicsSimpleTextItem::itemChange(change, value);
}
void ChordItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QFont f;
    auto rect = QGraphicsSimpleTextItem::boundingRect();
    f.setPointSize(12);
    painter->setPen(brush().color());
    painter->setFont(f);
    painter->drawText(rect.topRight() + QPoint{0, 16}, m_extstr);
    painter->drawText(rect.topRight() + QPoint{0, 32}, m_bassstr);
    QGraphicsSimpleTextItem::paint(painter, option, widget);
}
void ChordItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if (mouseEvent->modifiers() & Qt::ControlModifier) {
        mouseEvent->ignore();
    } else {
        emit itemSelected();
        QGraphicsItem::mousePressEvent(mouseEvent);
    }
}

QRectF ChordItem::boundingRect() const {
    auto rect = QGraphicsSimpleTextItem::boundingRect();
    if (!m_extstr.isEmpty() || !m_bassstr.isEmpty()) {
        auto length = std::max(m_extstr.length(), m_bassstr.length());
        auto botRight = rect.bottomRight();
        botRight.rx() += length * 10;
        botRight.ry() += m_bassstr.isEmpty() ? 0 : 8;
        rect.setBottomRight(botRight);
    }
    return rect;
}
