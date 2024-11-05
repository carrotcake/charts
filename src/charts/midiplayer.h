#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QObject>
#include <QThread>
#include <QTime>
#include "fluidsynth.h"
#include "src/charts/workingchord.h"

using namespace std::chrono_literals;

using fsynth = fluid_synth_t;
using fssettings = fluid_settings_t;
using fsdriver = fluid_audio_driver_t;

class MIDIPlayer : public QObject {
    Q_OBJECT
public:
    explicit MIDIPlayer(QObject *parent = nullptr);
    ~MIDIPlayer();
    void interruptPlayback() { m_interrupted = true; }
signals:

public slots:
    void previewChord(const Chord &chord, fsynth *synth) {
        const auto notes = chord.notes();
        m_interrupted = false;
        for (auto note : notes)
            fluid_synth_noteon(synth, 0, note.MIDIValue(), 100);
        for (size_t i = 0; i < 15 && !m_interrupted; ++i)
            QThread::sleep(50ms);
        fluid_synth_all_notes_off(synth, 0);
        m_interrupted = false;
    }

private:
    volatile bool m_interrupted;
};

class MIDIController : public QObject {
    Q_OBJECT

public:
    explicit MIDIController(QObject *parent = nullptr)
        : QObject(parent) {
        settings = new_fluid_settings();
        fluid_settings_setint(settings, "synth.polyphony", 128);
        fluid_settings_setnum(settings, "synth.gain", 1);
        synth = new_fluid_synth(settings);
        adriver = new_fluid_audio_driver(settings, synth);
        fluid_synth_sfload(synth, "GU-GS.sf2", 1);
        player.moveToThread(&playerthread);
        connect(&playerthread, &QThread::finished, &player, &QObject::deleteLater);
        connect(this, &MIDIController::previewRequested, &player, &MIDIPlayer::previewChord);
        playerthread.start();
    }
    ~MIDIController() {
        playerthread.quit();
        playerthread.wait();
        delete_fluid_audio_driver(adriver);
        delete_fluid_synth(synth);
        delete_fluid_settings(settings);
    }
public slots:
    void requestPreview(const WorkingChord &chord) {
        player.interruptPlayback();
        emit previewRequested(chord.getChord(), synth);
    }
signals:
    void previewRequested(const Chord &chord, fsynth *synth);

private:
    QThread playerthread;
    QTime lastrequest;
    MIDIPlayer player;
    fsynth *synth;
    fsdriver *adriver;
    fssettings *settings;
};

#endif // MIDIPLAYER_H
