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
    for (auto o : children()) {
        if (o->property("id") == id)
            o->deleteLater();
    }
    auto ptr = new ChordItem(seg.chord(), id, seg.measure(), seg.beat(), this);
    connect(ptr, &ChordItem::itemSelected, &seg, &ChordSeg::selected);
    addItem(ptr);
}
void ChartScene::addBarlineItem(int id, const BarlineSeg &seg) {
    auto ptr = new BarlineItem(id, seg.measure());
    addItem(ptr);
}

void ChartScene::addDittoItem(int id, const DittoSeg &seg) {
    const auto firstBeat = seg.beat() == 0;
    const auto str = QString(firstBeat ? "%" : "   ");
    auto ptr = new ChordItem(str, id, seg.measure(), seg.beat(), this);
    addItem(ptr);
}

void ChartScene::addLabelItem(int id, const LabelSeg &seg) {
    auto ptr = new LabelItem(seg.name(), id, seg.measure());
    addItem(ptr);
}
