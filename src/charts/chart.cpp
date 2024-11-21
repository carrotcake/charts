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
    connect(this, &Chart::segmentEdited, &m_view, &ChartScene::addChordItem);
    connect(this, &Chart::barlineAdded, &m_view, &ChartScene::addBarlineItem);
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
            if (beat != 0) {
                seg->setDitto();
                emit dittoSegAdded(*seg);
            } else {
                emit segmentEdited(*seg);
            }
            if (beat == 0 && measure % 8 == 0) {
                setLabel(c, seg->id());
                c = QChar(c.toLatin1() + 1);
            }
        }
        emit barlineAdded(measure);
    }

    m_sequence.setMeter(m_timesig);
    m_sequence.setTempo(200);
}

void Chart::setChord(const Chord &chord, int idx) {
    if (idx < 0 || idx > m_segments.size())
        return;
    auto seg = m_segments[idx];
    if (!seg)
        return;
    seg->setChord(chord);
    emit segmentEdited(*seg);
    init();
}

void Chart::setDitto(int idx) {
    if (idx < 0 || idx > m_segments.size())
        return;
    auto seg = m_segments[idx];
    if (!seg)
        return;
    seg->setDitto();
    emit dittoSegAdded(*seg);
    init();
}

void Chart::setNoChord(int idx) {
    if (idx < 0 || idx > m_segments.size())
        return;
    auto seg = m_segments[idx];
    if (!seg)
        return;
    seg->setNoChord();
    emit segmentEdited(*seg);
    init();
}

void Chart::setLabel(const QString &str, int idx) {
    if (idx < 0 || idx > m_segments.size())
        return;
    auto seg = m_segments[idx];
    if (!seg)
        return;
    seg->setLabel(str);
    emit labelAdded(idx, *seg);
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
    if (seg->isChord())
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
        if (seg->isChord())
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
        if (segIdx > idx)
            return lastID;
        lastID = seg->id();
    }
    return lastID;
}
