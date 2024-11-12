#ifndef SCALES_H
#define SCALES_H
#include "notes.h"

namespace Scales {
typedef std::array<bool, Notes::COUNT> interval_set;

enum class ScaleType { major, minor, melminor, harminor };
//                                                   #9      #11     #5
//                                           1 b9  9 b3  3 11 b5  5 b13 13 b7 7
static constexpr interval_set SCALESETS[] = {
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
};

enum class ModeType { ionian, dorian, phyrigian, lydian, mixolydian, aeolian, locrian };

} // namespace Scales

#endif // SCALES_H
