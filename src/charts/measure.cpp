#include "measure.h"

using namespace Meter;
using namespace Scales;
using namespace Notes;

Measure::Measure(bool isFirst, TimeSig time)
    : m_timesig(time) {
    m_beats = m_timesig.upper;
    Segment temp = {Chord(), KeySig(NOTES[NOTE_C], Scales::major, ionian), 1, false, true};
    if (isFirst)
        temp.isDitto = false;
    m_segments.push_back(temp);
    temp.isDitto = true;
    for (int i = 1; i < m_beats; ++i) {
        m_segments.push_back(temp);
    }
}

void Measure::placeChord(const WorkingChord& chord, qsizetype idx) {
    auto& seg = m_segments.at(idx);
    seg.chord = chord.getChord();
    seg.hasChord = true;
    seg.isDitto = false;
}

void Measure::placeNoChord(qsizetype idx) {
    auto& seg = m_segments.at(idx);
    seg.hasChord = false;
    seg.isDitto = false;
}

void Measure::removeChord(qsizetype idx) {
    auto& seg = m_segments.at(idx);
    seg.hasChord = false;
    seg.isDitto = true;
}

bool Measure::hasChordAtBeat(qsizetype idx) {
    auto& seg = m_segments.at(idx);
    return seg.hasChord;
}
bool Measure::hasDittoAtBeat(qsizetype idx) {
    auto& seg = m_segments.at(idx);
    return seg.isDitto;
}
