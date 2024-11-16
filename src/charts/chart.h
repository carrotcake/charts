#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QVector>
#include "src/charts/chartscene.h"
#include "src/charts/segment.h"

class Chart : public QObject {
    Q_OBJECT
public:
    explicit Chart(QObject *parent = nullptr, size_t measures = 32);
    void init();
    void addMeasure();
    ChartScene &view() { return m_view; }

signals:
    void chartUpdated();

private:
    QVector<Segment *> m_segments;
    ChartScene m_view;
    Scales::KeySig m_key;
    Meter::TimeSig m_timesig;
};

#endif // CHART_H
