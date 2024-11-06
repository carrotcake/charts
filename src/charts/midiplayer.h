#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QObject>
#include <QThread>
#include <QTime>
#include "src/charts/workingchord.h"
#include <fluidsynth.h>

using namespace std::chrono_literals;
using fsynth = fluid_synth_t;
using fssettings = fluid_settings_t;
using fsdriver = fluid_audio_driver_t;

class MIDIPlayer : public QObject {
    Q_OBJECT
public:
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
        m_fssettings = new_fluid_settings();
        fluid_settings_setint(m_fssettings, "synth.polyphony", 128);
        fluid_settings_setnum(m_fssettings, "synth.gain", 1);
        m_fsynth        = new_fluid_synth(m_fssettings);
        m_fsaudiodriver = new_fluid_audio_driver(m_fssettings, m_fsynth);
        fluid_synth_sfload(m_fsynth, "GU-GS.sf2", 1);
        m_player.moveToThread(&m_playerthread);
        connect(this, &MIDIController::previewRequested, &m_player, &MIDIPlayer::previewChord);
        // uncomment this if m_player ever becomes a pointer again
        // connect(&playerthread, &QThread::finished, &m_player, &QObject::deleteLater);
        m_playerthread.start();
    }
    ~MIDIController() {
        m_playerthread.quit();
        m_playerthread.wait();
        delete_fluid_audio_driver(m_fsaudiodriver);
        delete_fluid_synth(m_fsynth);
        delete_fluid_settings(m_fssettings);
    }
public slots:
    void requestPreview(const WorkingChord &chord) {
        m_player.interruptPlayback();
        emit previewRequested(chord.getChord(), m_fsynth);
    }
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
