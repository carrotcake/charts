#ifndef WORKINGCHORD_H
#define WORKINGCHORD_H
#include <QObject>
#include "src/music/chord.h"
class WorkingChord : public QObject {
    Q_OBJECT
public:
    WorkingChord()
        : m_chord() {}
    WorkingChord(const Notes::Note root, Chord::quality qual, Chord::extension ext)
        : m_chord(root, qual, ext) {}
    WorkingChord(const Notes::Note root,
                 Chord::quality qual,
                 Chord::extension ext,
                 Chord::Alterations& alts,
                 const Notes::Note bass)
        : m_chord(root, qual, ext, alts, bass) {}

    const auto& notes() const { return m_chord.notes(); }
    const auto& name() const { return m_chord.name(); }
    auto root() const { return m_chord.root(); }
    auto bass() const { return m_chord.bass(); }
    auto qual() const { return m_chord.qual(); }
    auto extensionLevel() const { return m_chord.extensionLevel(); }
    bool canAddAlteration(Chord::alteration alt) const { return m_chord.canAddAlteration(alt); }
    bool hasAlteration(Chord::alteration alt) const { return m_chord.hasAlteration(alt); }

public slots:
    void setRoot(const Notes::Note root) { m_chord.setRoot(root); }
    void setBass(const Notes::Note bass) { m_chord.setBass(bass); }
    void setQuality(Chord::quality qual) { m_chord.setQuality(qual); }
    void setExtension(Chord::extension ext) { m_chord.setExtension(ext); }
    void addAlteration(Chord::alteration alt) { m_chord.addAlteration(alt); }
    void removeAlteration(Chord::alteration alt) { m_chord.removeAlteration(alt); }
    void removeAllAlterations() { m_chord.removeAllAlterations(); }

signals:
    void rootChanged(Notes::value root);
    void bassChanged(Notes::value bass);
    void extensionChanged(Chord::extension ext);
    void alterationAdded(Chord::alteration alt);
    void alterationRemoved(Chord::alteration alt);

private:
    Chord m_chord;
};

#endif // WORKINGCHORD_H
