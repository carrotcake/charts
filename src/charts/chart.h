#pragma once

#include <QObject>
#include <QVector>
#include "src/charts/midisequence.h"
#include "src/music/meter.h"
#include "src/music/scales.h"
#include "src/ui/chartscene.h"
#include "workingchord.h"

class Chart : public QObject {
    Q_OBJECT
public:
    explicit Chart(QObject *parent = nullptr, size_t measures = 32);
    void init();
    void addMeasure();
    ChartScene &view() { return m_view; }
    void setChord(const Chord &chord, int idx);
    void setDitto(int idx);
    void setNoChord(int idx);
    void setLabel(const QString &str, int idx);
    auto selected() const { return m_selected; }
public slots:
    void changeSelection(size_t id);
    void initiatePlayback();
    void setTempo(size_t tempo);
    void processMIDITick(int tick);
signals:
    void chartUpdated();
    void chordClicked(const WorkingChord &chord);
    void segmentEdited(const Segment &seg);
    void barlineAdded(int measure);
    void dittoSegAdded(const Segment &seg);
    void labelAdded(int idx, const Segment &seg);
    void repeatSegAdded(int idx, const Segment &seg);
    void sequenceGenerated(const char *data, size_t len);
    void seekToTick(int tick);

private:
    void generateMIDISequence();
    int getSegmentByTick(size_t tick);
    QVector<Segment *> m_segments;
    ChartScene m_view;
    MIDISequence m_sequence;
    Scales::KeySig m_key;
    Meter::TimeSig m_timesig;
    size_t m_selected = -1, masterIdx = 0;
};
