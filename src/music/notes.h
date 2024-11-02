#ifndef NOTES_H
#define NOTES_H
#include <string>

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
static std::string str_ROMANMAJ[COUNT]
    = {"I", "bII", "II", "bIII", "III", "IV", "bV", "V", "bVI", "VI", "bVII", "VII"};
static std::string str_ROMANMIN[COUNT]
    = {"i", "bii", "ii", "biii", "iii", "iv", "bv", "v", "bvi", "vi", "bvii", "vii"};
static std::string str_NASHVILLE[COUNT]
    = {"1", "b2", "2", "b3", "3", "4", "b5", "5", "b6", "6", "b7", "7"};
static std::string str_FLATNAMES[COUNT]
    = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
static std::string str_SHARPNAMES[COUNT]
    = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};

struct Note{
    std::string flatName() const {return m_value == ERRNOTE ? "err" : str_FLATNAMES[m_value];}
    std::string sharpName() const {return m_value == ERRNOTE ? "err" :  str_SHARPNAMES[m_value];}
    bool const accidental(){
        switch(m_value){
        case Notes::value::NOTE_A:
        case Notes::value::NOTE_B:
        case Notes::value::NOTE_D:
        case Notes::value::NOTE_E:
        case Notes::value::NOTE_G:
            return false;
        default:
            break;
        }
        return true;
    }
    value m_value;
};

const Note A{NOTE_A},As{NOTE_Asharp},Bb{NOTE_Bflat},
    B{NOTE_B},C{NOTE_C},Cs{NOTE_Csharp},
    Db{NOTE_Dflat},D{NOTE_D},Ds{NOTE_Dsharp},
    Eb{NOTE_Eflat},E{NOTE_E},F{NOTE_F},
    Fs{NOTE_Fsharp},Gb{NOTE_Gflat},G{NOTE_G},
    Gs{NOTE_Gsharp},Ab{NOTE_Aflat};


} // namespace Notes

#endif // NOTES_H
