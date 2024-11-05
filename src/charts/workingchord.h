#ifndef WORKINGCHORD_H
#define WORKINGCHORD_H
#include <QObject>
#include "src/music/chord.h"
class WorkingChord : public QObject {
    Q_OBJECT
public:
    explicit WorkingChord(QObject* parent = nullptr)
        : QObject(parent)
        , m_chord() {}
    auto notes() const { return m_chord.notes(); }
    const auto& name() const { return m_chord.name(); }
    auto root() const { return m_chord.root(); }
    auto bass() const { return m_chord.bass(); }
    auto qual() const { return m_chord.qual(); }
    auto extensionLevel() const { return m_chord.extensionLevel(); }
    bool canAddAlteration(Chord::alteration alt) const { return m_chord.canAddAlteration(alt); }
    bool hasAlteration(Chord::alteration alt) const { return m_chord.hasAlteration(alt); }
    const auto& getChord() const { return m_chord; }
    void setRoot(const Notes::Note root);
    void setBass(const Notes::Note bass);
    void setQuality(Chord::quality qual);
    void setExtension(Chord::extension ext);
    void addAlteration(Chord::alteration alt);
    void removeAlteration(Chord::alteration alt);
    void removeAllAlterations();

signals:
    void rootChanged(Notes::Value root);
    void bassChanged(Notes::Value bass);
    void extensionChanged(Chord::extension ext);
    void qualityChanged(Chord::quality qual);
    void alterationAdded(Chord::alteration alt);
    void alterationRemoved(Chord::alteration alt);
    void alterationsReset();
    void rebuilt();

private:
    Chord m_chord;
};

#endif // WORKINGCHORD_H
