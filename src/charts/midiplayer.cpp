#include "midiplayer.h"

using namespace std::chrono_literals;

void MIDIPlayer::interruptPlayback() {
    m_interrupted = true;
}

void MIDIPlayer::previewChord(const Chord &chord, FSynth *synth) {
    const auto notes = chord.notes();
    m_interrupted = false; // hack
    for (auto note : notes)
        fluid_synth_noteon(synth, 0, note.MIDIValue(), 100);
    for (size_t i = 0; i < 15 && !m_interrupted; ++i)
        QThread::sleep(50ms); // big time hack
    fluid_synth_all_notes_off(synth, 0);
    m_interrupted = false; // still hacking
}

MIDIController::MIDIController(QObject *parent)
    : QObject(parent) {
    // fluidsynth initialization
    m_fssettings = new_fluid_settings();
    fluid_settings_setint(m_fssettings, "synth.polyphony", 128);
    fluid_settings_setnum(m_fssettings, "synth.gain", .8);
    m_fsynth = new_fluid_synth(m_fssettings);
    m_fsaudiodriver = new_fluid_audio_driver(m_fssettings, m_fsynth);
    fluid_synth_sfload(m_fsynth, "GU-GS.sf2", 1);
    //midi sequencing happens in its own thread so we can wait w/o blocking ui input
    m_player.moveToThread(&m_playerthread);
    connect(this, &MIDIController::previewRequested, &m_player, &MIDIPlayer::previewChord);
    // uncomment this if m_player ever becomes a pointer again
    // connect(&playerthread, &QThread::finished, &m_player, &QObject::deleteLater);
    m_playerthread.start();
}

MIDIController::~MIDIController() {
    m_playerthread.quit();
    m_playerthread.wait();
    delete_fluid_audio_driver(m_fsaudiodriver);
    delete_fluid_synth(m_fsynth);
    delete_fluid_settings(m_fssettings);
}

void MIDIController::requestPreview(const WorkingChord &tempchord) {
    m_player.interruptPlayback();                       //runs in main thread
    emit previewRequested(tempchord.chord(), m_fsynth); //runs in playerthread
}
