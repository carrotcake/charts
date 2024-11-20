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
    enum segtype { CHORD, DITTO, NOCHORD };
    Segment(segtype type, size_t len, size_t segID, QObject *parent = nullptr)
        : QObject{parent}
        , m_type(type)
        , m_length(len)
        , m_id(segID) {}
    size_t length() const { return m_length; }
    void setLength(size_t len) { m_length = len; }
    auto segType() const { return m_type; }
    auto id() const { return m_id; }
    auto tick() const { return m_tick; }
    void setTick(int tick) { m_tick = tick; }
    auto isNoChord() const { return m_noChord; }
    void setNoChord() { m_noChord = false; }
    auto isDitto() const { return m_isDitto; }
    auto setDitto() { m_isDitto = true; }
    const auto &chord() const { return m_chord; }
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
    segtype m_type;
    size_t m_length;
    size_t m_tick;
    const size_t m_id;
    WorkingChord m_chord;
    bool m_noChord;
    bool m_isDitto;
    QString m_label;
    size_t m_measure;
    size_t m_beat;
};
