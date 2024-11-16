#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QVector>
#include "src/charts/../ui/chartscene.h"
#include "src/charts/midiplayer.h"
#include "src/charts/segment.h"
#include "src/charts/workingchord.h"
#include "src/music/meter.h"
#include "src/music/scales.h"
#include <cstddef>

class Chart : public QObject {
    Q_OBJECT
public:
    explicit Chart(MIDIController &midi, QObject *parent = nullptr, size_t measures = 32);
    void init();
    void addMeasure();
    ChartScene &view() { return m_view; }
    void addChord(const Chord &chord, size_t measure, size_t beat, int idx = -1);
    void addBarline(size_t measure, int idx = -1);
    void addDitto(size_t measure, size_t beat, int idx = -1);
    void addLabel(const QString &str, size_t measure, int idx = -1);
public slots:
    void changeSelection(size_t id);

signals:
    void chartUpdated();
    void chordClicked(const WorkingChord &chord);
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
    MIDIController &m_midi;
};

#endif // CHART_H
