#include "chartscene.h"
#include <QCursor>
#include <QGraphicsItem>
#include "src/charts/segment.h"
#include "src/ui/barlineitem.h"
#include "src/ui/chorditem.h"
#include "src/ui/labelitem.h"

ChartScene::ChartScene(QObject *parent)
    : QGraphicsScene{parent} {
    this->setBackgroundBrush(Qt::darkGray);
    this->setSceneRect(0, 0, W, H);
    this->addRect(0, 0, W, H, QPen(Qt::black), QBrush(Qt::white));
}

void ChartScene::addChordItem(int id, const ChordSeg &seg) {
    auto ptr = new ChordItem(seg.chord(), id, seg.measure(), seg.beat(), this);
    connect(ptr, &ChordItem::itemSelected, &seg, &ChordSeg::selected);
    connect(&seg, &ChordSeg::destroyed, ptr, &ChordItem::deleteLater);
    addItem(ptr);
    clearSelection();
    ptr->setSelected(true);
}

void ChartScene::addBarlineItem(int id, const BarlineSeg &seg) {
    auto ptr = new BarlineItem(id, seg.measure());
    addItem(ptr);
}

void ChartScene::addDittoItem(int id, const DittoSeg &seg) {
    const auto firstBeat = seg.beat() == 0;
    const auto str = QString(firstBeat ? "%" : "   ");
    auto ptr = new ChordItem(str, id, seg.measure(), seg.beat(), this);
    connect(ptr, &ChordItem::itemSelected, &seg, &DittoSeg::selected);
    connect(&seg, &DittoSeg::destroyed, ptr, &ChordItem::deleteLater);
    addItem(ptr);
    clearSelection();
    ptr->setSelected(true);
}

void ChartScene::addLabelItem(int id, const LabelSeg &seg) {
    auto ptr = new LabelItem(seg.name(), id, seg.measure());
    addItem(ptr);
}

void ChartScene::selectItem(int id) {
    auto ptr = getItemByID(id);
    if (!ptr)
        return;
    clearSelection();
    ptr->setSelected(true);
}

QGraphicsItem *ChartScene::getItemByID(int id) {
    auto items = children();
    for (auto e : std::as_const(items)) {
        if (e->property("id") == id)
            return dynamic_cast<QGraphicsItem *>(e);
    }
    return nullptr;
}
