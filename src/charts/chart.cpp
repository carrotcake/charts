#include "chart.h"

using namespace Scales;
using namespace Notes;
using namespace Meter;

Chart::Chart(QObject *parent)
    : QObject{parent}
    , m_view(m_measures, this)
    , m_key(NOTES[NOTE_C], Scales::major, ionian)
    , m_timesig(TIMESIGS[FOURFOUR]) {
    m_measures.emplace_back(Measure(true));
    for (int i = 0; i < 31; ++i) {
        addMeasure();
    }
    connect(this, &Chart::chartUpdated, &m_view, &PrintingModel::updateView);
}

void Chart::init() {
    emit chartUpdated();
}

void Chart::addMeasure() {
    m_measures.emplace_back(Measure());
    emit chartUpdated();
}
