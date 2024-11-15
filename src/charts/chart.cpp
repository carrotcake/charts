#include "chart.h"

using namespace Scales;
using namespace Notes;
using namespace Meter;

Chart::Chart(QObject *parent)
    : QObject{parent}
    , m_view(this)
    , m_key(NOTES[NOTE_C], Scales::major, ionian)
    , m_timesig(TIMESIGS[FOURFOUR]) {
    connect(this, &Chart::chartUpdated, &m_view, &PrintingModel::updateView);
}

void Chart::init() {
    emit chartUpdated();
}
