#include "workingchord.h"

void WorkingChord::setRoot(const Notes::Note root) {
    m_chord.setRoot(root);
    emit rootChanged(root.val);
    emit rebuilt();
}
void WorkingChord::setBass(const Notes::Note bass) {
    m_chord.setBass(bass);
    emit bassChanged(bass.val);
    emit rebuilt();
}
void WorkingChord::setQuality(Chords::quality qual) {
    m_chord.setQuality(qual);
    emit qualityChanged(qual);
    emit rebuilt();
}
void WorkingChord::setExtension(Chords::extension ext) {
    m_chord.setExtension(ext);
    emit extensionChanged(ext);
    emit rebuilt();
}
void WorkingChord::addAlteration(Chords::alteration alt) {
    m_chord.addAlteration(alt);
    emit alterationAdded(alt);
    emit rebuilt();
}
void WorkingChord::removeAlteration(Chords::alteration alt) {
    m_chord.removeAlteration(alt);
    emit alterationRemoved(alt);
    emit rebuilt();
}
void WorkingChord::removeAllAlterations() {
    m_chord.removeAllAlterations();
    emit alterationsReset();
    emit rebuilt();
}

void WorkingChord::set(const Chord& chord) {
    m_chord = chord;
    emit rebuilt();
}
