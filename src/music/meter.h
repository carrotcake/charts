#ifndef METER_H
#define METER_H

namespace Meter {

enum class Subdiv {
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
    TimeSig(short upper, short lower)
        : m_upper(upper)
        , m_lower(lower) {};
    TimeSig()
        : TimeSig(4, 4) {};
    short upper() const { return m_upper; }
    short lower() const { return m_lower; }

private:
    const short m_upper, m_lower;
};

} // namespace Meter
#endif // METER_H
