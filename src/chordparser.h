#ifndef CHORDPARSER_H
#define CHORDPARSER_H

#include "music/chord.h"


class ChordParser
{
public:
    ChordParser();
    Chord parseChordFromString(const QString &str);
};

#endif // CHORDPARSER_H
