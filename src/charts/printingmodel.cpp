#include "printingmodel.h"
#include <QCursor>
#include <QGraphicsItem>

const static size_t h = 600, w = 420, margin = 80, cellw = 80, cellh = 60;

PrintingModel::PrintingModel(const std::vector<Measure> &measures, QObject *parent)
    : QGraphicsScene{parent}
    , m_measures(measures)
    , m_pix(w, h) {
    this->setBackgroundBrush(Qt::darkGray);

    auto e = this->addEllipse(0, 0, 100, 100, QPen(Qt::black));
    e->setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
    e->setCursor(Qt::CursorShape::PointingHandCursor);
    e->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable
                | QGraphicsItem::ItemIsFocusable);
}

void PrintingModel::updateView() {
    QPainter p(&m_pix);
    p.setBackground(Qt::white);
    p.fillRect(0, 0, w, h, Qt::white);
    p.setPen(Qt::black);
    for (size_t i = 0; i < m_measures.size(); ++i) {
        const auto &cur = m_measures.at(i);
        const size_t x = (i % 4) * cellw + margin, y = (i / 4) * cellh + margin;
        p.drawRect(x, y, cellw, cellh);
        p.drawText(x, y, QString::fromStdString(cur.chordAtBeat(0).name()));
    }
    emit viewUpdated();
}
