#pragma once

#include <QObject>
#include <QThread>
#include <QTime>
#include "src/charts/workingchord.h"
#include <fluidsynth.h>
#include <fluidsynth/types.h>

using FSynth = fluid_synth_t;
using FSynthSettings = fluid_settings_t;
using FSynthDriver = fluid_audio_driver_t;
using FSynthPlayer = fluid_player_t;

class MIDIPlayer : public QObject {
    Q_OBJECT

public:
    explicit MIDIPlayer(QObject *parent = nullptr)
        : QObject{parent} {}
    void interruptPlayback(FSynthPlayer *player);

public slots:
    void previewChord(const Chord &chord, FSynth *synth);
    void playbackData(FSynthPlayer *player);

private:
    volatile bool m_interrupted;
};

class MIDIController : public QObject {
    Q_OBJECT

public:
    explicit MIDIController(QObject *parent = nullptr);
    ~MIDIController();
    MIDIController(const MIDIController &other) = delete;
    MIDIController(MIDIController &&other) = delete;
    MIDIController &operator=(const MIDIController &other) = delete;

public slots:
    void requestPreview(const WorkingChord &chord);
    void loadData(const char *data, size_t len);
    void requestPlayback();
    void stopPlayback();

signals:
    void previewRequested(const Chord &chord, FSynth *synth);
    void playbackRequested(FSynthPlayer *player);

private:
    QThread m_playerthread;
    MIDIPlayer m_player;
    FSynth *m_fsynth;
    FSynthDriver *m_fsaudiodriver;
    FSynthSettings *m_fssettings;
    FSynthPlayer *m_fsplayer;
};
