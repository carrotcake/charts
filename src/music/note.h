#ifndef NOTE_H
#define NOTE_H

#include "notes.h"

class Note {
public:
    Note();

private:
    Notes::NoteLetter name;
    Notes::NoteValue val;
};

#endif // NOTE_H
