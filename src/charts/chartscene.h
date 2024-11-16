#ifndef CHARTSCENE_H
#define CHARTSCENE_H

#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QtTypes>
#include "src/charts/segment.h"

class ChartScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit ChartScene(QObject *parent = nullptr);

public slots:
    void updateView();
signals:
    void viewUpdated();

private:
};

#endif // CHARTSCENE_H
