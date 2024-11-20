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
    const auto beatlength = m_timesig.subdiv();
    m_segments.reserve(segcount);
    connect(this, &Chart::chordSegAdded, &m_view, &ChartScene::addChordItem);
    connect(this, &Chart::barlineSegAdded, &m_view, &ChartScene::addBarlineItem);
    connect(this, &Chart::dittoSegAdded, &m_view, &ChartScene::addDittoItem);
    connect(this, &Chart::labelAdded, &m_view, &ChartScene::addLabelItem);
    auto c = QChar('A');
    for (size_t measure = 0; measure < numMeasures; ++measure) {
        for (int beat = 0; beat < numBeats; ++beat) {
            //TODO: handle other subdivisions than quarter notes
            auto tick = m_sequence.ticksPerQuarterNote() * (measure * numBeats + beat);
            auto seg = m_segments.emplaceBack(
                new Segment(Segment::CHORD, beatlength, masterIdx++, this));
            seg->setMeasure(measure);
            seg->setBeat(beat);
            seg->setTick(tick);
            connect(seg, &Segment::segmentSelected, this, &Chart::changeSelection);
            emit chordSegAdded(*seg);
            if (beat == 0 && measure % 8 == 0) {
                addLabel(c, seg->id());
                c = QChar(c.toLatin1() + 1);
            }
        }
    }

    m_sequence.setMeter(m_timesig);
    m_sequence.setTempo(200);
}

void Chart::addChord(const Chord &chord, size_t measure, size_t beat, int idx) {
    auto ptr = m_segments[idx];
    ptr->setChord(chord);
    emit chordSegAdded(*ptr);
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

void Chart::addLabel(const QString &str, int idx) {
    if (idx < 0 || idx > m_segments.size())
        return;
    auto ptr = m_segments[idx];
    if (!ptr)
        return;
    ptr->setLabel(str);
    emit labelAdded(idx, *ptr);
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
    std::cout << "generated" << std::endl;
    m_sequence.clearSequence();
    Chord temp;
    for (auto seg : std::as_const(m_segments)) {
        size_t measure, beat, duration;
        if (!seg)
            continue;
        temp = seg->chord().chord();
        measure   = seg->measure();
        duration  = seg->length();
        beat      = seg->beat();
        auto tick = m_sequence.addChord(temp, measure, beat, duration);
        seg->setTick(tick);
    }
    auto data    = m_sequence.getRawData();
    auto dataLen = m_sequence.dataLength();
    std::cout << dataLen << std::endl;
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
