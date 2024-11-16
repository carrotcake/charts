#include "chorditem.h"
#include <QCursor>
#include <QFont>

ChordItem::ChordItem(const QString& str, QPoint coords) {
    QFont f;
    f.setPointSize(20);
    setText(str);
    setFont(f);
    coords.ry() += 16;
    coords.rx() += 4;
    setPos(coords);
    setCursor(Qt::CursorShape::PointingHandCursor);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
}
