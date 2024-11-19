#pragma once

#include "src/charts/workingchord.h"

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
    auto id() const { return m_id; }

protected:
    Segment(segtype type, size_t len, size_t segID, QObject *parent = nullptr)
        : QObject{parent}
        , m_type(type)
        , m_length(len)
        , m_id(segID) {}
    const segtype m_type;
    size_t m_length;
    const size_t m_id;
};

class ChordSeg : public Segment {
    Q_OBJECT
public:
    ChordSeg(const Chord &chord,
             size_t len,
             size_t id,
             size_t meas,
             size_t beat,
             QObject *parent = nullptr)
        : Segment(CHORD, len, id, parent)
        , m_chord(this, chord)
        , m_noChord(false)
        , m_measure(meas)
        , m_beat(beat) {}
    ChordSeg(size_t len, size_t id)
        : Segment(CHORD, len, id)
        , m_noChord(true) {}
    auto isNoChord() const { return m_noChord; }
    void setNoChord() { m_noChord = false; }
    auto isDitto() const { return m_isDitto; }
    auto setDitto() { m_isDitto = true; }
    const auto& chord() const { return m_chord; }
    void setChord(const Chord &chord) {
        m_isDitto = false;
        m_noChord = false;
        m_chord.set(chord);
    }
    auto measure() const { return m_measure; }
    void setMeasure(size_t measure) { m_measure = measure; }
    auto beat() const { return m_beat; }
    void setBeat(size_t beat) { m_beat = beat; }
    auto hasBarline() const { return m_beat == 0; }
    void setLabel(const QString &str) { m_label = str; };
    auto hasLabel() const { return !m_label.isEmpty(); }
    auto label() const { return m_label; }
public slots:
    void selected();

signals:
    void segmentSelected(size_t id);

private:
    WorkingChord m_chord;
    bool m_noChord;
    bool m_isDitto;
    QString m_label;
    size_t m_measure;
    size_t m_beat;
};

class DittoSeg : public Segment {
    Q_OBJECT
public:
    DittoSeg(size_t len, size_t id, size_t meas, size_t beat, QObject *parent = nullptr)
        : Segment(DITTO, len, id, parent)
        , m_measure(meas)
        , m_beat(beat) {}
    auto measure() const { return m_measure; }
    void setMeasure(size_t measure) { m_measure = measure; }
    auto beat() const { return m_beat; }
    void setBeat(size_t beat) { m_beat = beat; }
public slots:
    void selected();

signals:
    void segmentSelected(size_t id);

private:
    size_t m_measure;
    size_t m_beat;
};

class BarlineSeg : public Segment {
    Q_OBJECT
public:
    BarlineSeg(size_t id, size_t measure, QObject *parent = nullptr)
        : Segment(BARLINE, 0, id, parent)
        , m_measure(measure) {}
    auto measure() const { return m_measure; }
    void setMeasure(size_t measure) { m_measure = measure; }

private:
    size_t m_measure;
};

class LabelSeg : public Segment {
    Q_OBJECT
public:
    LabelSeg(const QString &str, size_t id, size_t measure, QObject *parent = nullptr)
        : Segment(LABEL, 0, id, parent)
        , m_measure(measure)
        , m_str(str) {}
    auto measure() const { return m_measure; }
    void setMeasure(size_t measure) { m_measure = measure; }
    const auto &name() const { return m_str; }
    void setName(const QString &str) { m_str = str; }

private:
    size_t m_measure;
    QString m_str;
};

class RepeatSeg : public Segment {
    Q_OBJECT
public:
    RepeatSeg(size_t id, QObject *parent = nullptr)
        : Segment(REPEAT, 0, id, parent) {}

public:
    auto isEnd() const { return m_isEnd; }

private:
    bool m_isEnd;
    int m_endings;
    int m_id;
};
