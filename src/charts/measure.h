#ifndef MEASURE_H
#define MEASURE_H

#include <QObject>
#include "src/music/chord.h"
#include "src/music/meter.h"
#include "src/music/scales.h"

struct Segment {
    Chord chord;
    Scales::KeySig key;
    qsizetype beats;
    bool hasChord;
};

class Measure : public QObject {
    Q_OBJECT
public:
    explicit Measure(QObject *parent = nullptr);

private:
    Meter::TimeSig m_timesig;
    qsizetype m_beats;
    std::list<Segment> m_segments;
signals:
};

#endif // MEASURE_H
