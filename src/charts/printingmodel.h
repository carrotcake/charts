#ifndef PRINTINGMODEL_H
#define PRINTINGMODEL_H

#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QtTypes>
#include "src/charts/measure.h"

class PrintingModel : public QObject {
    Q_OBJECT
public:
    explicit PrintingModel(const std::vector<Measure> &measures, QObject *parent = nullptr);

public slots:
    void updateView();
signals:
    void viewUpdated(const QPixmap &pix);

private:
    const std::vector<Measure> &m_measures;
    QPixmap m_pix;
};

#endif // PRINTINGMODEL_H
