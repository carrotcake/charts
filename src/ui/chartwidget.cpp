#include "chartwidget.h"
#include <QPainter>
#include <QRandomGenerator>
#include <QtTypes>

ChartWidget::ChartWidget(QWidget *parent)
    : QGraphicsView{parent} {
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform
                   | QPainter::TextAntialiasing | QPainter::LosslessImageRendering);
    setResizeAnchor(AnchorViewCenter);
}

void ChartWidget::updatePixmap() {
    update();
}
