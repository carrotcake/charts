#include "src/charts/segment.h"
void ChordSeg::selected() {
    emit segmentSelected(m_id);
}
void DittoSeg::selected() {
    emit segmentSelected(m_id);
}
