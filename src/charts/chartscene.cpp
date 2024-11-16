#include "chartscene.h"
#include <QCursor>
#include <QGraphicsItem>
#include "src/ui/chorditem.h"

const static size_t h = 1000, w = 700, margin = 50, cellw = 150, cellh = 60;

ChartScene::ChartScene(QObject *parent)
    : QGraphicsScene{parent} {
    this->setBackgroundBrush(Qt::darkGray);
    this->setSceneRect(0, 0, w, h);
    this->addRect(0, 0, w, h, QPen(Qt::black), QBrush(Qt::white));
}

void ChartScene::updateView() {
    auto coords = QPoint(0, 0);
    auto &x = coords.rx(), &y = coords.ry(), bars = -1, chords = 0;
    QFont f;
    f.setPointSize(16);
    this->clear();
    this->addRect(0, 0, w, h, QPen(Qt::black), QBrush(Qt::white));
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
