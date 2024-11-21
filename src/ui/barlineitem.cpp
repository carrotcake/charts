#include "barlineitem.h"
#include "chartscene.h"

BarlineItem::BarlineItem(size_t measure)
    : m_measure(measure) {
    const auto margin = ChartScene::MARGIN, width = ChartScene::CELLW, height = ChartScene::CELLH,
               offset = ChartScene::VERTOFFSET;
    auto xIdx = measure % 4, yIdx = measure / 4;
    QPoint coords;
    coords.setX(xIdx * width + margin);
    coords.setY(yIdx * height + margin + yIdx * offset);
    if (xIdx == 0) {
        setLine(margin, coords.y() + height, ChartScene::W - margin, coords.y() + height);
    } else {
        setLine(coords.x(), coords.y(), coords.x(), coords.y() + height);
    }
}
