#ifndef SEGMENT_H
#define SEGMENT_H

#include "src/charts/workingchord.h"
#include "src/music/chord.h"
#include "src/music/meter.h"
#include "src/music/scales.h"

/*
 *  Segment type: 
 *      - barline
 *      - chord / no chord
 *      - ditto
 *      - decoration (label)
 *      - repeat
 */

class Segment : public QObject {
    Q_OBJECT
public:
    enum segtype { CHORD, DITTO, BARLINE, LABEL, REPEAT };
    virtual size_t length() const { return m_length; }
    void setLength(size_t len) { m_length = len; }
    auto segType() const { return m_type; }

protected:
    Segment(segtype type, size_t len, QObject *parent = nullptr)
        : QObject{parent}
        , m_type(type)
        , m_length(len) {}

private:
    const segtype m_type;
    size_t m_length;
};

class ChordSeg : public Segment {
    Q_OBJECT
public:
    ChordSeg(const Chord &chord, size_t len, QObject *parent = nullptr)
        : Segment(CHORD, len, parent)
        , m_chord(this, chord)
        , m_noChord(false) {}
    ChordSeg(size_t len)
        : Segment(CHORD, len)
        , m_noChord(true) {}
    auto isNoChord() const { return m_noChord; }
    void setNoChord() { m_noChord = false; }
    const auto& chord() const { return m_chord; }
    void setChord(const Chord& chord) { m_chord.set(chord); }

private:
    WorkingChord m_chord;
    bool m_noChord;
};

class DittoSeg : public Segment {
    Q_OBJECT
public:
    DittoSeg(size_t len, QObject *parent = nullptr)
        : Segment(DITTO, len, parent) {}
};

class BarlineSeg : public Segment {
    Q_OBJECT
public:
    BarlineSeg(QObject *parent = nullptr)
        : Segment(BARLINE, 0, parent) {}
};

class LabelSeg : public Segment {
    Q_OBJECT
    LabelSeg(const QString &str, QObject *parent = nullptr)
        : Segment(LABEL, 0, parent)
        , m_str(str) {}

private:
    QString m_str;
};

class RepeatSeg : public Segment {
    Q_OBJECT
    RepeatSeg(QObject *parent = nullptr)
        : Segment(REPEAT, 0, parent) {}

private:
    bool m_isEnd;
    int m_endings;
    int m_id;
};

#endif // SEGMENT_H
