#ifndef CHART_H
#define CHART_H

#include <QObject>
#include "src/charts/measure.h"
#include "src/charts/printingmodel.h"

class Chart : public QObject {
    Q_OBJECT

    struct Repeat {
        qsizetype start;
        std::vector<qsizetype> endpoints;
    };

public:
    explicit Chart(QObject *parent = nullptr);

signals:
private:
    std::vector<Measure> m_measures;
    PrintingModel m_view;
    Scales::KeySig m_key;
    Meter::TimeSig m_timesig;
};

#endif // CHART_H
