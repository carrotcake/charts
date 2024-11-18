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
    void addChord(const Chord &chord, size_t measure, size_t beat, int idx = -1);
    void setChord(const Chord &chord, int idx);
    void addBarline(size_t measure, int idx = -1);
    void addDitto(size_t measure, size_t beat, int idx = -1);
    void addLabel(const QString &str, size_t measure, int idx = -1);
    auto selected() const { return m_selected; }
public slots:
    void changeSelection(size_t id);
    void initiatePlayback();
    void setTempo(size_t tempo);
signals:
    void chartUpdated();
    void chordClicked(const WorkingChord &chord);
    void chordSegAdded(int idx, const ChordSeg &seg);
    void barlineSegAdded(int idx, const BarlineSeg &seg);
    void dittoSegAdded(int idx, const DittoSeg &seg);
    void labelSegAdded(int idx, const LabelSeg &seg);
    void repeatSegAdded(int idx, const RepeatSeg &seg);
    void sequenceGenerated(const char *data, size_t len);

private:
    void generateMIDISequence();
    QVector<Segment *> m_segments;
    ChartScene m_view;
    MIDISequence m_sequence;
    Scales::KeySig m_key;
    Meter::TimeSig m_timesig;
    size_t m_selected = -1, masterIdx = 0;
};
