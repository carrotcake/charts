#include "scorewidget.h"
#include <QPainter>

ScoreWidget::ScoreWidget(QWidget *parent)
    : QWidget{parent} {}

void ScoreWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    const int h = height(), w = width();
    p.fillRect(0, 0, w, h, Qt::white);
    for (int x = 0; x < w; x += 10) {
        for (int y = 0; y < h; y += 10) {
            p.setPen(QColor(x * 255 / w, y * 255 / h, 0));
            p.drawRect(x, y, 5, 5);
        }
    }
}
