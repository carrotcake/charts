#ifndef NOTES_H
#define NOTES_H
namespace Notes {

enum class NoteValue {
    A      = 0,
    Asharp = 1,
    Bflat  = 1,
    B      = 2,
    Cflat  = 2,
    Bsharp = 3,
    C      = 3,
    Csharp = 4,
    Dflat  = 4,
    D      = 5,
    Dsharp = 6,
    Eflat  = 6,
    E      = 7,
    Fflat  = 7,
    Esharp = 8,
    F      = 8,
    Fsharp = 9,
    Gflat  = 9,
    G      = 10,
    Gsharp = 11,
    Aflat  = 11
};

enum class Interval {
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

static const char* str_ROMANMAJ[]
    = {"I", "bII", "II", "bIII", "III", "IV", "bV", "V", "bVI", "VI", "bVII", "VII"};

static const char* str_ROMANMIN[]
    = {"i", "bii", "ii", "biii", "iii", "iv", "bv", "v", "bvi", "vi", "bvii", "vii"};

static const char* str_NASHVILLE[]
    = {"1", "b2", "2", "b3", "3", "4", "b5", "5", "b6", "6", "b7", "7"};

enum class FlatNotes { A, Bb, B, C, Db, D, Eb, E, F, Gb, G, Ab };
static const char* str_FLATNAMES[]
    = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};

enum class SharpNotes { A, As, B, C, Cs, D, Ds, E, F, Fs, G, Gs };
static const char* str_SHARPNAMES[]
    = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};

enum class NoteLetter { A = 0, B, C, D, E, F, G };
enum class Octave { A0 = 0, A1, A2, A3, A4, A5, A6, A7 };

} // namespace Notes

#endif // NOTES_H
