#include "midisequence.h"
#include "src/music/meter.h"

MIDISequence::MIDISequence(QObject *parent)
    : QObject{parent} {
    m_file.makeDeltaTicks();
}

void MIDISequence::addChord(const Chord &chord, int measure, int beat, int duration) {
    auto tpq = m_file.getTPQ();
    auto pnotes = chord.notes();
    auto startTick = tpq * beat + tpq * measure * 4;
    auto endTick = startTick + tpq * duration / Meter::QUARTER;
    for (auto note : pnotes) {
        auto key = note.MIDIValue();
        m_file.addNoteOn(0, startTick, CHORDCHANNEL, key, 70);
        m_file.addNoteOff(0, endTick, CHORDCHANNEL, key);
    }
    m_file.sortTracks();
}
void MIDISequence::clearSequence() {
    m_file.clear();
}

void MIDISequence::writeToFile() {
    m_file.write("test.mid");
}
