#include "midiplayer.h"
#include <fluidsynth/midi.h>

using namespace std::chrono_literals;

void MIDIPlayer::interruptPlayback(FSynthPlayer *player) {
    fluid_player_stop(player);
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

void MIDIPlayer::playbackData(FSynthPlayer *player) {
    fluid_player_play(player);
    fluid_player_join(player);
}

MIDIController::MIDIController(QObject *parent)
    : QObject{parent} {
    // fluidsynth initialization
    m_fssettings = new_fluid_settings();
    fluid_settings_setint(m_fssettings, "synth.polyphony", 128);
    /* there's like a 1/10 chance that the audio driver initializing
       creates an artifact and makes my speakers pop if I don't do this
       ok never mind it doesn't even work (linux only?) */
    fluid_settings_setnum(m_fssettings, "synth.gain", 0);

    m_fsynth = new_fluid_synth(m_fssettings);
    m_fsplayer = new_fluid_player(m_fsynth);
    m_fsaudiodriver = new_fluid_audio_driver(m_fssettings, m_fsynth);
    fluid_synth_sfload(m_fsynth, "GU-GS.sf2", 1);
    fluid_settings_setnum(m_fssettings, "synth.gain", 1);
    //midi sequencing happens in its own thread so we can wait w/o blocking ui input
    m_player.moveToThread(&m_playerthread);
    connect(this, &MIDIController::previewRequested, &m_player, &MIDIPlayer::previewChord);
    connect(this, &MIDIController::playbackRequested, &m_player, &MIDIPlayer::playbackData);
    // uncomment this if m_player ever becomes a pointer again
    // connect(&playerthread, &QThread::finished, &m_player, &QObject::deleteLater);
    m_playerthread.start();
}

MIDIController::~MIDIController() {
    fluid_player_stop(m_fsplayer);
    m_playerthread.quit();
    m_playerthread.wait();
    delete_fluid_audio_driver(m_fsaudiodriver);
    delete_fluid_player(m_fsplayer);
    delete_fluid_synth(m_fsynth);
    delete_fluid_settings(m_fssettings);
}

void MIDIController::requestPreview(const WorkingChord &tempchord) {
    m_player.interruptPlayback(m_fsplayer);             //runs in main thread
    emit previewRequested(tempchord.chord(), m_fsynth); //runs in playerthread
}
void MIDIController::loadData(const char *data, size_t len) {
    if (fluid_player_get_total_ticks(m_fsplayer) > 0) {
        delete_fluid_player(m_fsplayer);
        m_fsplayer = new_fluid_player(m_fsynth);
    }
    fluid_player_add_mem(m_fsplayer, data, len);
}

void MIDIController::requestPlayback() {
    auto status = fluid_player_get_status(m_fsplayer);
    if (status == FLUID_PLAYER_READY || status == FLUID_PLAYER_DONE)
        emit playbackRequested(m_fsplayer);
}

void MIDIController::stopPlayback() {
    fluid_player_stop(m_fsplayer);
}

void MIDIController::setGain(double gain) {
    fluid_settings_setnum(m_fssettings, "synth.gain", gain);
}
