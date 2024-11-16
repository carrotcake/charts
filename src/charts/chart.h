#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QVector>
#include "src/charts/../ui/chartscene.h"
#include "src/charts/segment.h"
#include "src/music/meter.h"
#include "src/music/scales.h"
#include <cstddef>

class Chart : public QObject {
    Q_OBJECT
public:
    explicit Chart(QObject *parent = nullptr, size_t measures = 32);
    void init();
    void addMeasure();
    ChartScene &view() { return m_view; }
    void addChord(const Chord &chord, size_t measure, size_t beat, int idx = -1);
    void addBarline(size_t measure, int idx = -1);
    void addDitto(size_t measure, size_t beat, int idx = -1);
    void addLabel(const QString &str, size_t measure, int idx = -1);
signals:
    void chartUpdated();
    void chordSegAdded(int idx, const ChordSeg &seg);
    void barlineSegAdded(int idx, const BarlineSeg &seg);
    void dittoSegAdded(int idx, const DittoSeg &seg);
    void labelSegAdded(int idx, const LabelSeg &seg);
    void repeatSegAdded(int idx, const RepeatSeg &seg);

private:
    QVector<Segment *> m_segments;
    ChartScene m_view;
    Scales::KeySig m_key;
    Meter::TimeSig m_timesig;
};

#endif // CHART_H
