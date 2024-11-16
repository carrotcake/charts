#include "chorditem.h"
#include <QCursor>
#include <QFont>
#include "chartscene.h"

ChordItem::ChordItem(const QString& str, size_t id, size_t measure, size_t beat)
    : m_id(id)
    , m_measure(measure)
    , m_beat(beat) {
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
}
