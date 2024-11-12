#ifndef SCALES_H
#define SCALES_H
#include "notes.h"

namespace Scales {

typedef std::array<bool, Notes::COUNT> interval_set;

enum ScaleType { major, minor, melminor, harminor };
//                                                   #9      #11     #5
//                                           1 b9  9 b3  3 11 b5  5 b13 13 b7 7
static constexpr interval_set SCALESETS[] = {
    /*************************************/ {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1}, //major - 1,2,3,4,5,6,7
    /*************************************/ {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0}, //minor - 1,2,b3,4,5,b6,b7
    /*************************************/ {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1}, //melodic minor - 1,2,b3,4,5,6,7
    /*************************************/ {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1}, //harmonic minor - 1,2,b3,4,5,b6,7
};

enum ModeType { ionian = 0, dorian, phyrigian, lydian, mixolydian, aeolian, locrian };

struct KeySig {
    Notes::Note tonic;
    ScaleType quality;
    ModeType mode;
};

} // namespace Scales

#endif // SCALES_H
