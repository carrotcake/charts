#ifndef METER_H
#define METER_H

namespace Meter {

enum Subdiv {
    SIXTYFOURTH = 1,
    THIRTYSECOND = 2,
    SIXTEENTH = 4,
    EIGTH = 8,
    QUARTER = 16,
    HALF = 32,
    WHOLE = 64
};

const static double DOTTED = 1.5, TRIPLE = 2. / 3.;

struct TimeSig {
public:
    inline auto subdiv() {
        switch (lower) {
        case 1:
            return WHOLE;
        case 2:
            return HALF;
        case 8:
            return EIGTH;
        case 16:
            return SIXTEENTH;
        case 32:
            return THIRTYSECOND;
        case 64:
            return SIXTYFOURTH;
        default:
            return QUARTER;
        }
    }
    const short upper, lower;
};

enum timesigs {
    FOURFOUR = 0,
    TWOFOUR,
    THREEFOUR,
    FIVEFOUR,
    SIXFOUR,
    SEVENFOUR,
    SIXEIGHT,
    TWELVEEIGHT
};

static constexpr TimeSig TIMESIGS[]
    = {{4, 4}, {2, 4}, {3, 4}, {5, 4}, {6, 4}, {7, 4}, {6, 8}, {12, 8}};

} // namespace Meter
#endif // METER_H
