#include "chart.h"
#include <QRandomGenerator>
#include "src/charts/midiplayer.h"

using namespace Scales;
using namespace Notes;
using namespace Meter;

Chart::Chart(MIDIController &midi, QObject *parent, size_t numMeasures)
    : QObject{parent}
    , m_view(this)
    , m_key(NOTES[NOTE_C], Scales::major, ionian)
    , m_timesig(TIMESIGS[FOURFOUR])
    , m_midi(midi) {
    const auto numBeats = m_timesig.upper;
    const auto segcount = numMeasures * m_timesig.upper;
    m_segments.reserve(segcount + numMeasures);

    connect(this, &Chart::chordClicked, &m_midi, &MIDIController::requestPreview);
    connect(this, &Chart::chordSegAdded, &m_view, &ChartScene::addChordItem);
    connect(this, &Chart::barlineSegAdded, &m_view, &ChartScene::addBarlineItem);
    connect(this, &Chart::dittoSegAdded, &m_view, &ChartScene::addDittoItem);
    connect(this, &Chart::labelSegAdded, &m_view, &ChartScene::addLabelItem);

    auto r = QRandomGenerator();
    QChar c = 'A';
    for (size_t measure = 0; measure < numMeasures; ++measure) {
        addBarline(measure);
        if (measure % 8 == 0) {
            addLabel(c, measure);
            c = QChar(c.toLatin1() + 1);
        }
        for (int beat = 0; beat < numBeats; ++beat) {
            //TODO: handle other subdivisions than quarter notes
            if (beat % 2 == 0 && r.bounded(2) == 1) {
                Chord c;
                c.setRoot(Notes::NOTES[r.bounded(int(Notes::COUNT))]);
                c.setBass(c.root());
                c.setQuality(static_cast<Chords::quality>(r.bounded(Chords::minMaj)));
                addChord(c, measure, beat);
            } else {
                addDitto(measure, beat);
            }
        }
    }
}

void Chart::addChord(const Chord &chord, size_t measure, size_t beat, int idx) {
    const auto beatlength = m_timesig.subdiv();
    if (idx == -1)
        idx = m_segments.size();
    auto ptr = new ChordSeg(chord, beatlength, m_segments.size(), measure, beat, this);
    connect(ptr, &ChordSeg::segmentSelected, this, &Chart::changeSelection);
    m_segments.emplace(idx, ptr);
    emit chordSegAdded(idx, *ptr);
}

void Chart::addDitto(size_t measure, size_t beat, int idx) {
    const auto beatlength = m_timesig.subdiv();
    if (idx == -1)
        idx = m_segments.size();
    auto ptr = new DittoSeg(beatlength, m_segments.size(), measure, beat, this);
    m_segments.emplace(idx, ptr);
    emit dittoSegAdded(idx, *ptr);
}

void Chart::addBarline(size_t measure, int idx) {
    if (idx == -1)
        idx = m_segments.size();
    auto ptr = new BarlineSeg(idx, measure, this);
    m_segments.emplace(idx, ptr);
    emit barlineSegAdded(idx, *ptr);
}

void Chart::addLabel(const QString &str, size_t measure, int idx) {
    if (idx == -1)
        idx = m_segments.size();
    auto ptr = new LabelSeg(str, idx, measure, this);
    m_segments.emplace(idx, ptr);
    emit labelSegAdded(idx, *ptr);
}

void Chart::init() {
    emit chartUpdated();
}

void Chart::changeSelection(size_t id) {
    auto seg = dynamic_cast<ChordSeg *>(m_segments[id]);
    if (!seg)
        return;
    emit chordClicked(seg->chord());
}
