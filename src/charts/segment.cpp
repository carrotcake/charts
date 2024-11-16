
#include "src/charts/segment.h"
void ChordSeg::selected() {
    if (this->isNoChord())
        return;
    emit segmentSelected(m_id);
}
