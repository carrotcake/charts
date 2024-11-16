#include "chart.h"
#include <QRandomGenerator>

using namespace Scales;
using namespace Notes;
using namespace Meter;

Chart::Chart(QObject *parent, size_t measures)
    : QObject{parent}
    , m_view(this)
    , m_key(NOTES[NOTE_C], Scales::major, ionian)
    , m_timesig(TIMESIGS[FOURFOUR]) {
    const auto beats = m_timesig.upper;
    const auto beatlength = Meter::subdivFromDenominator(m_timesig.lower);
    const auto segcount = measures * m_timesig.upper;

    auto r = QRandomGenerator();

    m_segments.reserve(segcount + measures);
    for (size_t i = 0; i < measures; ++i) {
        m_segments.emplace_back(new BarlineSeg(this));
        for (int j = 0; j < beats; ++j) {
            //TODO: handle other subdivisions than quarter notes
            if (j % 2 == 0 && r.bounded(2) == 1) {
                Chord c;
                c.setRoot(Notes::NOTES[r.bounded(int(Notes::COUNT))]);
                c.setBass(c.root());
                c.setQuality(static_cast<Chords::quality>(r.bounded(Chords::minMaj)));
                m_segments.emplace_back(new ChordSeg(c, beatlength, this));
            } else {
                m_segments.emplace_back(new DittoSeg(beatlength, this));
            }
        }
    }

    connect(this, &Chart::chartUpdated, &m_view, &ChartScene::updateView);
}

void Chart::init() {
    emit chartUpdated();
}
