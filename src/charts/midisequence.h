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
    void setTempo(int tempo);
    void setMeter(const Meter::TimeSig meter) { m_meter = meter; }
    int addChord(const Chord &chord, int measure, int beat, int duration);
    void clearSequence();
    void writeToFile();
    const char *getRawData();
    auto dataLength() const { return m_data.length(); }
signals:

private:
    const int CHORDCHANNEL = 0;
    int m_tempo;
    Meter::TimeSig m_meter;
    smf::MidiFile m_file;
    std::string m_data;
};

#endif // MIDISEQUENCE_H
