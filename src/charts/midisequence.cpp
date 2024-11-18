#include "midisequence.h"
#include "src/music/meter.h"
#include <sstream>

MIDISequence::MIDISequence(QObject *parent)
    : QObject{parent}
    , m_tempo(200) {
    m_file.makeDeltaTicks();
    m_file.addTempo(0, 0, m_tempo);
}

void MIDISequence::setTempo(int tempo) {
    m_tempo = tempo;
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
    m_file.addTempo(0, 0, m_tempo);
    m_file.sortTracks();
}
/*
 * 	VERY LARGE std::string COPIED OUT OF THIS FUNCTION
 * 	 - CONTAINS ENTIRE MIDI FILE
 *   - this terrifies the c++ deveolper
 * 	 - YES THIS IS 'EXPENSIVE'
 *   - could just hold the string as a member and return the const char* data
 * 	 - WILL FIX IF IT ENDS UP BEING A PROBLEM
 */
const char *MIDISequence::getRawData() {
    std::stringstream stream;
    if (!m_file.write(stream))
        m_data = "";
    else
        m_data = stream.str();
    return m_data.data();
}

void MIDISequence::writeToFile() {
    std::stringstream stream;
    if (!m_file.write(stream))
        return;
    std::cout << stream.str() << std::endl;
    m_file.write("test.mid");
}
