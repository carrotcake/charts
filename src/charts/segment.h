#ifndef SEGMENT_H
#define SEGMENT_H

#include "src/charts/workingchord.h"
#include "src/music/chord.h"
#include "src/music/meter.h"
#include "src/music/scales.h"

// struct Segment {
//     Chord chord;
//     Scales::KeySig key;
//     size_t beats;
//     bool hasChord;
//     bool isDitto;
// };

// class Measure {
// public:
//     Measure(bool isFirst = false, Meter::TimeSig time = Meter::TIMESIGS[Meter::FOURFOUR]);
//     void placeChord(const WorkingChord &chord, size_t idx);
//     void placeNoChord(size_t idx);
//     void removeChord(size_t idx);
//     bool hasChordAtBeat(size_t idx);
//     bool hasDittoAtBeat(size_t idx);
//     const Chord &chordAtBeat(size_t idx) const { return m_segments.at(idx).chord; }
//     size_t beats() const { return m_beats; }
//     Meter::TimeSig timeSig() const { return m_timesig; }

// private:
//     Meter::TimeSig m_timesig;
//     size_t m_beats;
//     std::vector<Segment> m_segments;
// };

/*
 *  Segment type: 
 *      - barline
 *      - chord / no chord
 *      - ditto
 *      - decoration (label)
 *      - repeat
 */

class Segment {
public:
    auto length() const { return m_length; }
    void setLength(size_t len) { m_length = len; }

protected:
    enum segtype { CHORD, DITTO, BARLINE, LABEL, REPEAT };
    Segment(segtype type, size_t len)
        : m_type(type)
        , m_length(len) {}
    auto segType() const { return m_type; }
    void setType(segtype type) { m_type = type; }

private:
    segtype m_type;
    size_t m_length;
};

class ChordSeg : public Segment {
public:
    ChordSeg(const Chord& chord, size_t len)
        : Segment(CHORD, len)
        , m_chord(chord)
        , m_hasChord(true) {}
    ChordSeg(size_t len)
        : Segment(CHORD, len)
        , m_hasChord(false) {}
    auto isNoChord() const { return m_hasChord; }
    void setNoChord() { m_hasChord = false; }
    const auto& chord() const { return m_chord; }
    void setChord(const Chord& chord) { m_chord = chord; }

private:
    Chord m_chord;
    bool m_hasChord;
};

class DittoSeg : public Segment {
public:
    DittoSeg(size_t len)
        : Segment(DITTO, len) {}
};

class BarlineSeg : public Segment {
public:
    BarlineSeg()
        : Segment(BARLINE, 0) {}
};

class LabelSeg : public Segment {
    LabelSeg()
        : Segment(LABEL, 0) {}
};

class RepeatSeg : public Segment {
    RepeatSeg()
        : Segment(REPEAT, 0) {}
};

#endif // SEGMENT_H
