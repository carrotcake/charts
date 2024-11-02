#ifndef NOTE_H
#define NOTE_H

#include "notes.h"

struct PitchedNote {
public:
    PitchedNote(const Notes::Note val, Notes::Octave oct)
        : m_note(val),
        m_octave(oct){}
    Notes::Note const note(){return m_note;}
    Notes::Octave const value(){return m_octave;}
private:
    const Notes::Note m_note;
    Notes::Octave m_octave;
};

#endif // NOTE_H
