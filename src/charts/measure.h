#ifndef MEASURE_H
#define MEASURE_H

#include "src/charts/workingchord.h"
#include "src/music/chord.h"
#include "src/music/meter.h"
#include "src/music/scales.h"

struct Segment {
    Chord chord;
    Scales::KeySig key;
    qsizetype beats;
    bool hasChord;
    bool isDitto;
};

class Measure {
public:
    Measure(bool isFirst = false, Meter::TimeSig time = Meter::TIMESIGS[Meter::FOURFOUR]);
    void placeChord(const WorkingChord &chord, qsizetype idx);
    void placeNoChord(qsizetype idx);
    void removeChord(qsizetype idx);
    bool hasChordAtBeat(qsizetype idx);
    bool hasDittoAtBeat(qsizetype idx);
    const Chord &chordAtBeat(qsizetype idx) const { return m_segments.at(idx).chord; }
    qsizetype beats() const { return m_beats; }
    Meter::TimeSig timeSig() const { return m_timesig; }

private:
    Meter::TimeSig m_timesig;
    qsizetype m_beats;
    std::vector<Segment> m_segments;
};

#endif // MEASURE_H
