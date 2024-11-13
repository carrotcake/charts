#include "scorewidget.h"
#include <QPainter>
#include <QtTypes>
#include <QRandomGenerator>

ChartWidget::ChartWidget(QWidget *parent)
    : QWidget{parent}
    , m_pix() {}

void ChartWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    const int h = height(), w = width();
    const double r = (double) w / (double) h;
    int ph = h, pw = w;
    if (r > .7)
        pw = h * .7;
    else
        ph = w * (1. / .7);
    p.fillRect(0, 0, w, h, Qt::darkGray);

    p.drawPixmap((w - pw) / 2, (h - ph) / 2, pw, ph, m_pix);
    // for (int x = 0; x < w; x += 10) {
    //     for (int y = 0; y < h; y += 10) {
    //         qint32 rgb = QRandomGenerator::global()->generate();
    //         p.setBrush(QColor(rgb & 255, (rgb >> 8) & 255, (rgb >> 16) & 255));
    //         p.fillRect(x, y, 10, 10, p.brush());
    //     }
    // }
}

void ChartWidget::updatePixmap(const QPixmap &pix) {
    m_pix = pix;
    this->update();
}
