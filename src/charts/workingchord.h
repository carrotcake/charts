#ifndef WORKINGCHORD_H
#define WORKINGCHORD_H
#include <QObject>
#include "src/music/chord.h"
class WorkingChord : public QObject {
    Q_OBJECT
public:
    explicit WorkingChord(QObject* parent = nullptr, Chord chord = Chord())
        : QObject(parent)
        , m_chord(chord) {}
    auto notes() const { return m_chord.notes(); }
    const auto& name() const { return m_chord.name(); }
    auto root() const { return m_chord.root(); }
    auto bass() const { return m_chord.bass(); }
    auto qual() const { return m_chord.qual(); }
    auto extensionLevel() const { return m_chord.extensionLevel(); }
    bool canAddAlteration(Chords::alteration alt) const { return m_chord.canAddAlteration(alt); }
    bool hasAlteration(Chords::alteration alt) const { return m_chord.hasAlteration(alt); }
    const auto& chord() const { return m_chord; }
    void setRoot(const Notes::Note root);
    void setBass(const Notes::Note bass);
    void setQuality(Chords::quality qual);
    void setExtension(Chords::extension ext);
    void addAlteration(Chords::alteration alt);
    void removeAlteration(Chords::alteration alt);
    void removeAllAlterations();
    void set(const Chord& chord);

signals:
    void rootChanged(Notes::Value root);
    void bassChanged(Notes::Value bass);
    void extensionChanged(Chords::extension ext);
    void qualityChanged(Chords::quality qual);
    void alterationAdded(Chords::alteration alt);
    void alterationRemoved(Chords::alteration alt);
    void alterationsReset();
    void rebuilt();

private:
    Chord m_chord;
};

#endif // WORKINGCHORD_H
