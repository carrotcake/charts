#include "chart.h"
#include <QRandomGenerator>
#include "src/charts/segment.h"
#include "src/music/chord.h"
#include <utility>

using namespace Scales;
using namespace Notes;
using namespace Meter;

Chart::Chart(QObject *parent, size_t numMeasures)
    : QObject{parent}
    , m_view(this)
    , m_key(NOTES[NOTE_C], Scales::major, ionian)
    , m_timesig(TIMESIGS[FOURFOUR]) {
    const auto numBeats = m_timesig.upper;
    const auto segcount = numMeasures * m_timesig.upper;
    m_segments.resize((segcount + numMeasures) * 2);
    connect(this, &Chart::chordSegAdded, &m_view, &ChartScene::addChordItem);
    connect(this, &Chart::barlineSegAdded, &m_view, &ChartScene::addBarlineItem);
    connect(this, &Chart::dittoSegAdded, &m_view, &ChartScene::addDittoItem);
    connect(this, &Chart::labelSegAdded, &m_view, &ChartScene::addLabelItem);
    auto r = QRandomGenerator::global();
    auto c = QChar('A');
    for (size_t measure = 0; measure < numMeasures; ++measure) {
        addBarline(measure);
        if (measure % 8 == 0) {
            addLabel(c, measure);
            c = QChar(c.toLatin1() + 1);
        }
        for (int beat = 0; beat < numBeats; beat += 2) {
            //TODO: handle other subdivisions than quarter notes
            if (r->bounded(2) == 1) {
                Chord c;
                c.setRoot(Notes::NOTES[r->bounded(int(Notes::COUNT))]);
                c.setBass(c.root());
                c.setQuality(static_cast<Chords::quality>(r->bounded(Chords::minMaj + 1)));
                c.setExtension(static_cast<Chords::extension>(r->bounded(Chords::thirteen + 1)));
                if (r->bounded(20) < 2)
                    c.setBass(Notes::NOTES[r->bounded(int(Notes::COUNT))]);
                addChord(c, measure, beat);
            } else {
                addDitto(measure, beat);
            }
        }
    }
    m_sequence.setMeter(m_timesig);
    m_sequence.setTempo(200);
}

void Chart::addChord(const Chord &chord, size_t measure, size_t beat, int idx) {
    const auto beatlength = m_timesig.subdiv() * 2;
    if (idx == -1)
        idx = masterIdx++;
    auto ptr = m_segments[idx];
    connect(ptr, &Segment::segmentSelected, this, &Chart::changeSelection);
    emit chordSegAdded(idx, *ptr);
    init();
}

void Chart::setChord(const Chord &chord, int idx) {
    if (idx < 0 || idx > m_segments.size())
        return;
    auto seg = m_segments[idx];
    if (!seg)
        return;
    addChord(chord, seg->measure(), seg->beat(), idx);
}

void Chart::addDitto(size_t measure, size_t beat, int idx) {
    const auto beatlength = m_timesig.subdiv() * 2;
    if (idx == -1)
        idx = masterIdx++;
    auto ptr = m_segments[idx];
    if (!ptr)
        return;
    connect(ptr, &Segment::segmentSelected, this, &Chart::changeSelection);
    emit dittoSegAdded(idx, *ptr);
    init();
}

void Chart::addBarline(size_t measure, int idx) {
    if (idx == -1)
        idx = masterIdx++;
    auto ptr = m_segments[idx];
    if (!ptr)
        return;
    emit barlineSegAdded(idx, *ptr);
    init();
}

void Chart::addLabel(const QString &str, size_t measure, int idx) {
    if (idx == -1)
        idx = masterIdx++;
    auto ptr = m_segments[idx];
    if (!ptr)
        return;
    ptr->setLabel(str);
    emit labelSegAdded(idx, *ptr);
    init();
}

void Chart::init() {
    generateMIDISequence();
    emit chartUpdated();
}

void Chart::changeSelection(size_t id) {
    m_selected = id;
    auto seg   = m_segments[id];
    if (!seg)
        return;
    auto approxTick = (seg->measure() * m_timesig.lower + seg->beat())
                      * m_sequence.ticksPerQuarterNote();
    emit seekToTick(approxTick);
    emit chordClicked(seg->chord());
}

void Chart::initiatePlayback() {
    
}

void Chart::setTempo(size_t tempo) {
    m_sequence.setTempo(tempo);
}

void Chart::processMIDITick(int tick) {
    auto segID = getSegmentByTick(tick);
    if (segID < 0)
        return;
    m_view.selectItem(segID);
}

void Chart::generateMIDISequence() {
    m_sequence.clearSequence();
    Chord temp;
    for (auto seg : std::as_const(m_segments)) {
        size_t measure, beat, duration;
        if (!seg)
            continue;
        if (seg->segType() == Segment::CHORD)
            temp = seg->chord().chord();
        measure   = seg->measure();
        duration  = seg->length();
        beat      = seg->beat();
        auto tick = m_sequence.addChord(temp, measure, beat, duration);
        seg->setTick(tick);
    }
    auto data    = m_sequence.getRawData();
    auto dataLen = m_sequence.dataLength();
    emit sequenceGenerated(data, dataLen);
}

int Chart::getSegmentByTick(size_t tick) {
    auto idx    = tick / m_sequence.ticksPerQuarterNote();
    auto lastID = -1;
    for (auto seg : std::as_const(m_segments)) {
        if (!seg)
            continue;
        auto measure = seg->measure();
        auto beat    = seg->beat();
        auto segIdx  = measure * m_timesig.lower + beat;
        if (segIdx > idx) {
            return lastID;
        }
        lastID = seg->id();
    }
    return lastID;
}
