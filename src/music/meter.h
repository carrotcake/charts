#ifndef METER_H
#define METER_H

#include <QtTypes>

namespace Meter {
enum class Subdivision {
    SIXTYFOURTH  = 1,
    THIRTYSECOND = 2,
    SIXTEENTH    = 4,
    EIGTH        = 8,
    QUARTER      = 16,
    HALF         = 32,
    WHOLE        = 64
};

const static double DOTTED = 1.5, TRIPLE = 2. / 3.;

struct TimeSig {
public:
    const quint8 upper, lower;
    TimeSig(const quint8 top, const quint8 btm)
        : upper(top)
        , lower(btm) {};
    TimeSig()
        : TimeSig(4, 4) {};
};
} // namespace Meter
#endif // METER_H
