#include "printingmodel.h"
#include <QCursor>
#include <QGraphicsItem>

const static size_t h = 1000, w = 700, margin = 80, cellw = 80, cellh = 60;

PrintingModel::PrintingModel(QObject *parent)
    : QGraphicsScene{parent}
    , m_pix(w, h) {
    this->setBackgroundBrush(Qt::darkGray);
    this->setSceneRect(0, 0, w, h);
    this->addRect(0, 0, w, h, QPen(Qt::black), QBrush(Qt::white));
    auto e = this->addEllipse(0, 0, 100, 100, QPen(Qt::black));
    e->setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
    e->setCursor(Qt::CursorShape::PointingHandCursor);
    e->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable
                | QGraphicsItem::ItemIsFocusable);
}
