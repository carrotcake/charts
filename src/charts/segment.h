#pragma once

#include "src/charts/workingchord.h"

/*
 *  Segment: 
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
        , m_id(segID)
        , m_type(type)
        , m_length(len) {}
    size_t length() const { return m_length; }
    void setLength(size_t len) { m_length = len; }
    auto segType() const { return m_type; }
    auto id() const { return m_id; }
    auto tick() const { return m_tick; }
    void setTick(int tick) { m_tick = tick; }
    auto isChord() const { return m_type == CHORD; }
    auto isNoChord() const { return m_type == NOCHORD; }
    void setNoChord() {
        m_type = NOCHORD;
    }
    auto isDitto() const { return m_type == DITTO; }
    auto setDitto() { m_type = DITTO; }
    const auto &chord() const { return m_chord; }
    void setChord(const Chord &chord) {
        m_type = CHORD;
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
    const size_t m_id;
    segtype m_type;
    size_t m_measure;
    size_t m_beat;
    size_t m_length;
    size_t m_tick;
    QString m_label;
    WorkingChord m_chord;
};
