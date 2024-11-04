#ifndef NOTES_H
#define NOTES_H

#include <string>
#include <array>

namespace Notes {

const size_t COUNT = 12;

enum value {
    ERRNOTE=-1,
    NOTE_C      = 0,
    NOTE_Dflat  ,
    NOTE_D      ,
    NOTE_Eflat  ,
    NOTE_E      ,
    NOTE_F      ,
    NOTE_Gflat  ,
    NOTE_G      ,
    NOTE_Aflat  ,
    NOTE_A      ,
    NOTE_Bflat  ,
    NOTE_B
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

enum class Letter { C = 0, D, E, F, G, A, B };
enum class Octave { A0 = 1, A1, A2, A3, A4, A5, A6, A7 };

const std::array<const std::string, COUNT> str_ROMANMAJ
    = {"I", "♭II", "II", "♭III", "III", "IV", "bV", "V", "♭VI", "VI", "♭VII", "VII"};
const std::array<const std::string, COUNT> str_ROMANMIN
    = {"i", "♭ii", "ii", "♭iii", "iii", "iv", "bv", "v", "♭vi", "vi", "♭vii", "vii"};
const std::array<const std::string, COUNT> str_NASHVILLE
    = {"1", "♭2", "2", "b3", "3", "4", "♭5", "5", "♭6", "6", "♭7", "7"};
const std::array<const std::string, COUNT> str_FLATNAMES
    = { "C", "Db", "D", "E♭", "E", "F", "Gb", "G", "A♭","A", "B♭", "B"};
const std::array<const std::string, COUNT> str_SHARPNAMES
    = { "C", "C♯", "D", "D♯", "E", "F", "F♯", "G", "G#","A", "A♯", "B",};
const std::array<const std::string, COUNT> str_BOTHNAMES
    = {"C", "C♯ / D♭", "D", "D♯ / Eb", "E", "F", "F♯ / G♭", "G", "G♯ / A♭","A", "A♯ / B♭", "B"};

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

static constexpr Note NOTES[] = {Note{NOTE_C},
                                 Note{NOTE_Dflat},
                                 Note{NOTE_D},
                                 Note{NOTE_Eflat},
                                 Note{NOTE_E},
                                 Note{NOTE_F},
                                 Note{NOTE_Gflat},
                                 Note{NOTE_G},
                                 Note{NOTE_Aflat},
                                 Note{NOTE_A},
                                 Note{NOTE_Bflat},
                                 Note{NOTE_B}};

} // namespace Notes

#endif // NOTES_H
