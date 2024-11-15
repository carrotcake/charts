#ifndef CHART_H
#define CHART_H

#include <QObject>
#include "src/charts/printingmodel.h"
#include "src/charts/segment.h"

class Chart : public QObject {
    Q_OBJECT

    struct Repeat {
        qsizetype start;
        std::vector<qsizetype> endpoints;
    };

public:
    explicit Chart(QObject *parent = nullptr);
    void init();
    void addMeasure();
    PrintingModel &view() { return m_view; }

signals:
    void chartUpdated();

private:
    std::vector<Segment> m_segments;
    PrintingModel m_view;
    Scales::KeySig m_key;
    Meter::TimeSig m_timesig;
};

#endif // CHART_H
