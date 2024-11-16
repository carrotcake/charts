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
    const auto str = QString::fromStdString(seg.chord().name());
    auto ptr = new ChordItem(str, id, seg.measure(), seg.beat());
    addItem(ptr);
}
void ChartScene::addBarlineItem(int id, const BarlineSeg &seg) {
    auto ptr = new BarlineItem(id, seg.measure());
    addItem(ptr);
}

void ChartScene::addDittoItem(int id, const DittoSeg &seg) {
    const auto firstBeat = seg.beat() == 0;
    const auto str = QString(firstBeat ? "%" : "   ");
    auto ptr = new ChordItem(str, id, seg.measure(), seg.beat());
    addItem(ptr);
}

void ChartScene::addLabelItem(int id, const LabelSeg &seg) {
    auto ptr = new LabelItem(seg.name(), id, seg.measure());
    addItem(ptr);
}

void ChartScene::updateView() {
    // f.setPointSize(16);
    //this->clear();
    //this->addRect(0, 0, w, h, QPen(Qt::black), QBrush(Qt::white));
    // for (auto i = 0; i < m_segments.size(); ++i) {
    //     auto seg = m_segments.at(i);
    //     switch (seg->segType()) {
    //     case Segment::CHORD:
    //         {
    //             chords++;
    //             auto e = dynamic_cast<ChordSeg *>(seg);
    //             if (e->isNoChord()) {
    //                 addItem(new ChordItem("N.C.", coords));
    //             } else {
    //                 addItem(new ChordItem(QString::fromStdString(e->chord().name()), coords));
    //             }
    //             break;
    //         }
    //     case Segment::DITTO:
    //         {
    //             chords++;
    //             if (chords == 1)
    //                 addItem(new ChordItem("%", coords));
    //             else
    //                 addItem(new ChordItem("   ", coords));
    //             break;
    //         }
    //     case Segment::BARLINE:
    //         {
    //             bars++;
    //             chords = 0;
    //             if (bars % 4 == 0 && bars != 0)
    //                 this->addLine(margin, y + cellh, w - margin, y + cellh);
    //             else
    //                 this->addLine(x, y, x, y + cellh);
    //             break;
    //         }
    //     case Segment::LABEL:
    //         {
    //             break;
    //         }
    //     case Segment::REPEAT:
    //         {
    //             break;
    //         }
    //     }
    //     x = (bars % 4) * cellw + chords * (cellw / 4) + margin;
    //     y = (bars / 4) * cellh + margin;
    // }
    emit viewUpdated();
}
