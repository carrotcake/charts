#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QObject>
#include <QThread>
#include <QTime>
#include "src/charts/workingchord.h"
#include <fluidsynth.h>

using fsynth = fluid_synth_t;
using fssettings = fluid_settings_t;
using fsdriver = fluid_audio_driver_t;

class MIDIPlayer : public QObject {
    Q_OBJECT

public:
    void interruptPlayback();

public slots:
    void previewChord(const Chord &chord, fsynth *synth);

private:
    volatile bool m_interrupted;
};

class MIDIController : public QObject {
    Q_OBJECT

public:
    explicit MIDIController(QObject *parent = nullptr);
    ~MIDIController();
    MIDIController(MIDIController &other) = delete;
    MIDIController(MIDIController &&other) = delete;
    MIDIController &operator=(const MIDIController &other) = delete;

public slots:
    void requestPreview(const WorkingChord &chord);

signals:
    void previewRequested(const Chord &chord, fsynth *synth);

private:
    QThread m_playerthread;
    MIDIPlayer m_player;
    fsynth *m_fsynth;
    fsdriver *m_fsaudiodriver;
    fssettings *m_fssettings;
};

#endif // MIDIPLAYER_H
