#include "labelitem.h"
#include <QCursor>
#include <QGraphicsItem>
#include "chartscene.h"

LabelItem::LabelItem(const QString &str, size_t id, size_t measure)
    : m_id(id)
    , m_measure(measure) {
    const auto margin = ChartScene::MARGIN, width = ChartScene::CELLW, height = ChartScene::CELLH,
               offset = ChartScene::VERTOFFSET;
    auto xIdx = measure % 4, yIdx = measure / 4;
    QPoint coords;
    QFont f;
    coords.setX(xIdx * width + margin);
    coords.setY(yIdx * height + margin / 2 + yIdx * offset);
    f.setPointSize(22);
    setFont(f);
    setText(str);
    setPos(coords);
    setCursor(Qt::PointingHandCursor);
    setFlags(ItemIsSelectable | ItemIsFocusable);
}

QRectF LabelItem::boundingRect() const {
    auto rect = QGraphicsSimpleTextItem::boundingRect();
    auto topLeft = rect.topLeft(), botRight = rect.bottomRight();
    topLeft.rx() -= 4;
    topLeft.ry() -= 1;
    botRight.rx() += 4;
    botRight.ry() += 1;
    rect.setTopLeft(topLeft);
    rect.setBottomRight(botRight);
    return rect;
}

void LabelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());
    QGraphicsSimpleTextItem::paint(painter, option, widget);
}
