#ifndef PRINTINGMODEL_H
#define PRINTINGMODEL_H

#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QtTypes>
#include "src/charts/segment.h"

class PrintingModel : public QGraphicsScene {
    Q_OBJECT
public:
    explicit PrintingModel(QObject *parent = nullptr);

public slots:
    void updateView();
signals:
    void viewUpdated();

private:
    QPixmap m_pix;
};

#endif // PRINTINGMODEL_H
