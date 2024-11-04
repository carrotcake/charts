#include "scorewidget.h"
#include <QPainter>
#include <QtTypes>
#include <QRandomGenerator>

ScoreWidget::ScoreWidget(QWidget *parent)
    : QWidget{parent} {}

void ScoreWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    const int h = height(), w = width();
    p.fillRect(0, 0, w, h, Qt::white);
    // for (int x = 0; x < w; x += 10) {
    //     for (int y = 0; y < h; y += 10) {
    //         qint32 rgb = QRandomGenerator::global()->generate();
    //         p.setBrush(QColor(rgb & 255, (rgb >> 8) & 255, (rgb >> 16) & 255));
    //         p.fillRect(x, y, 10, 10, p.brush());
    //     }
    // }
}
