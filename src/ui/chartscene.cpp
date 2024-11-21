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

void ChartScene::addChordItem(const Segment &seg) {
    const auto id = seg.id();
    auto ptr = getItemByID(id);
    if (ptr) {
        auto item = dynamic_cast<ChordItem *>(ptr);
        item->changeChord(seg.chord());
    } else {
        auto item = new ChordItem(seg.chord(), id, seg.measure(), seg.beat(), this);
        connect(item, &ChordItem::itemSelected, &seg, &Segment::selected);
        connect(&seg, &Segment::destroyed, item, &ChordItem::deleteLater);
        addItem(item);
        ptr = item;
    }
    clearSelection();
    ptr->setSelected(true);
}

void ChartScene::addDittoItem(const Segment &seg) {
    const auto id = seg.id();
    const auto firstBeat = seg.beat() == 0;
    const auto str = QString(firstBeat ? "%" : "   ");
    auto ptr = getItemByID(id);
    if (ptr) {
        auto item = dynamic_cast<ChordItem *>(ptr);
        item->setDitto();
    } else {
        auto item = new ChordItem(str, id, seg.measure(), seg.beat(), this);
        connect(item, &ChordItem::itemSelected, &seg, &Segment::selected);
        connect(&seg, &Segment::destroyed, item, &ChordItem::deleteLater);
        addItem(item);
        ptr = item;
    }
    clearSelection();
    ptr->setSelected(true);
}

void ChartScene::addBarlineItem(int measure) {
    auto ptr = new BarlineItem(measure);
    addItem(ptr);
}

void ChartScene::addLabelItem(int id, const Segment &seg) {
    auto ptr = new LabelItem(seg.label(), id, seg.measure());
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
