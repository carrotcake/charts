#pragma once

#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QtTypes>
#include "src/charts/segment.h"

class ChartScene : public QGraphicsScene {
    Q_OBJECT
public:
    static constexpr size_t H = 1000, W = 700, MARGIN = 50, CELLW = 150, CELLH = 60,
                            VERTOFFSET = 30;
    explicit ChartScene(QObject *parent = nullptr);

public slots:
    void updateView() {};
    void addChordItem(const Segment &seg);
    void addBarlineItem(int measure);
    void addDittoItem(const Segment &seg);
    void addLabelItem(int id, const Segment &seg);
    void selectItem(int id);
signals:
    void viewUpdated();

private:
    QGraphicsItem *getItemByID(int id);
};

