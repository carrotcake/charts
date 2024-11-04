#ifndef NOTES_H
#define NOTES_H

#include <string>
#include <array>

namespace Notes {

const size_t COUNT = 12;

enum value {
    ERRNOTE=-1,
    NOTE_A      = 0,
    NOTE_Asharp = 1,
    NOTE_Bflat  = 1,
    NOTE_B      = 2,
    NOTE_C      = 3,
    NOTE_Csharp = 4,
    NOTE_Dflat  = 4,
    NOTE_D      = 5,
    NOTE_Dsharp = 6,
    NOTE_Eflat  = 6,
    NOTE_E      = 7,
    NOTE_F      = 8,
    NOTE_Fsharp = 9,
    NOTE_Gflat  = 9,
    NOTE_G      = 10,
    NOTE_Gsharp = 11,
    NOTE_Aflat  = 11
};

enum interval {
    UNISON     = 0,
    MINSECOND  = 1,
    MAJSECOND  = 2,
    AUGSECOND  = 3,
    MINTHIRD   = 3,
    MAJTHIRD   = 4,
    PERFOURTH  = 5,
    AUGFOURTH  = 6,
    DIMFIFTH   = 6,
    PERFIFTH   = 7,
    AUGFIFTH   = 8,
    MINSIXTH   = 8,
    MAJSIXTH   = 9,
    MINSEVENTH = 10,
    MAJSEVENTH = 11,
    OCTAVE     = 12
};

enum class Letter { A = 0, B, C, D, E, F, G };
enum class Octave { A0 = 0, A1, A2, A3, A4, A5, A6, A7 };

const std::array<const std::string, COUNT> str_ROMANMAJ
    = {"I", "♭II", "II", "♭III", "III", "IV", "bV", "V", "♭VI", "VI", "♭VII", "VII"};
const std::array<const std::string, COUNT> str_ROMANMIN
    = {"i", "♭ii", "ii", "♭iii", "iii", "iv", "bv", "v", "♭vi", "vi", "♭vii", "vii"};
const std::array<const std::string, COUNT> str_NASHVILLE
    = {"1", "♭2", "2", "b3", "3", "4", "♭5", "5", "♭6", "6", "♭7", "7"};
const std::array<const std::string, COUNT> str_FLATNAMES
    = {"A", "B♭", "B", "C", "Db", "D", "E♭", "E", "F", "Gb", "G", "A♭"};
const std::array<const std::string, COUNT> str_SHARPNAMES
    = {"A", "A♯", "B", "C", "C♯", "D", "D♯", "E", "F", "F♯", "G", "G#"};
const std::array<const std::string, COUNT> str_BOTHNAMES
    = {"A", "A♯ / B♭", "B", "C", "C♯ / D♭", "D", "D♯ / Eb", "E", "F", "F♯ / G♭", "G", "G♯ / A♭"};

struct Note {
    const std::string& flatName() const {
        return m_value == ERRNOTE ? str_FLATNAMES[0] : str_FLATNAMES[m_value];
    }
    const std::string& sharpName() const {
        return m_value == ERRNOTE ? str_FLATNAMES[0] : str_SHARPNAMES[m_value];
    }
    bool accidental() const {
        switch(m_value){
        case Notes::value::NOTE_A:
        case Notes::value::NOTE_B:
        case Notes::value::NOTE_D:
        case Notes::value::NOTE_E:
        case Notes::value::NOTE_G:
            return false;
        default:
            return true;
        }
    }
    value m_value;
};

static constexpr Note NOTES[] = {Note{NOTE_A},
                                 Note{NOTE_Bflat},
                                 Note{NOTE_B},
                                 Note{NOTE_C},
                                 Note{NOTE_Dflat},
                                 Note{NOTE_D},
                                 Note{NOTE_Eflat},
                                 Note{NOTE_E},
                                 Note{NOTE_F},
                                 Note{NOTE_Gflat},
                                 Note{NOTE_G},
                                 Note{NOTE_Aflat}};

} // namespace Notes

#endif // NOTES_H
