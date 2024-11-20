#include "src/charts/segment.h"
void Segment::selected() {
    emit segmentSelected(m_id);
}
