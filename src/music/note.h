#ifndef NOTE_H
#define NOTE_H

#include "notes.h"

struct PitchedNote {
public:
    PitchedNote(const Notes::Note val, Notes::Octave oct)
        : m_note(val)
        , m_octave(oct) {}
    Notes::Note note() const { return m_note; }
    Notes::Octave value() const { return m_octave; }
    int MIDIValue() const { return 12 * static_cast<int>(m_octave) + m_note.val; }

private:
    const Notes::Note m_note;
    Notes::Octave m_octave;
};

#endif // NOTE_H
