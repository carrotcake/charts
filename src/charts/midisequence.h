#ifndef MIDISEQUENCE_H
#define MIDISEQUENCE_H

#include <QObject>
#include "MidiFile.h"
#include "src/music/chord.h"
#include "src/music/meter.h"

class MIDISequence : public QObject {
    Q_OBJECT
public:
    explicit MIDISequence(QObject *parent = nullptr);
    void setTempo(int tempo) { m_tempo = tempo; }
    void setMeter(const Meter::TimeSig meter) { m_meter = meter; }
    void addChord(const Chord &chord, int measure, int beat, int duration);
    void clearSequence();
    void writeToFile();
signals:

private:
    const int CHORDCHANNEL = 0;
    int m_tempo;
    Meter::TimeSig m_meter;
    smf::MidiFile m_file;
};

#endif // MIDISEQUENCE_H
