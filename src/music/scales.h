#pragma once

#include "notes.h"
#include <vector>

namespace Scales {

typedef std::array<bool, Notes::COUNT> interval_set;

enum ScaleType { major, melminor, harminor };
//                                                   #9      #11     #5
//                                           1 b9  9 b3  3 11 b5  5 b13 13 b7 7
static constexpr interval_set SCALESETS[] = {
    /*************************************/ {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1}, //major - 1,2,3,4,5,6,7
    /*************************************/ {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1}, //melodic minor - 1,2,b3,4,5,6,7
    /*************************************/ {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1}, //harmonic minor - 1,2,b3,4,5,b6,7
};

enum ModeType { ionian = 0, dorian, phyrigian, lydian, mixolydian, aeolian, locrian };

struct KeySig {
public:
    KeySig(Notes::Note tonic, ScaleType qual, ModeType mode)
        : m_tonic(tonic)
        , m_quality(qual)
        , m_mode(mode) {
        size_t mode_offset = 0;
        for (size_t idx = 0, count = 0; idx < Notes::COUNT && count < mode; ++idx, ++mode_offset) {
            if (SCALESETS[m_quality][idx])
                count++;
        }
        for (size_t idx = 0; idx < Notes::COUNT; ++idx) {
            const auto realidx = (idx + mode_offset) % Notes::COUNT;
            if (SCALESETS[m_quality][realidx]) {
                const auto val = (m_tonic.val + idx) % Notes::COUNT;
                m_notes.push_back(Notes::NOTES[val]);
            }
        }
    }
    auto tonic() const { return m_tonic; }
    auto quality() const { return m_quality; }
    auto mode() const { return m_mode; }
    const auto& notes() const { return m_notes; }

private:
    Notes::Note m_tonic;
    ScaleType m_quality;
    ModeType m_mode;
    std::vector<Notes::Note> m_notes;
};

} // namespace Scales
