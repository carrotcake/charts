#include "midiplayer.h"
#include "src/music/chord.h"
#include <fluidsynth/midi.h>
#include <iostream>

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

int MIDIPlayer::seek(FSynthPlayer *player, int tick) {
    return fluid_player_seek(player, tick);
}

MIDIController::MIDIController(QObject *parent)
    : QObject{parent} {
    // fluidsynth initialization
    m_fssettings = new_fluid_settings();
    fluid_settings_setint(m_fssettings, "synth.polyphony", 128);
    fluid_settings_setnum(m_fssettings, "synth.gain", 0);

    // recommended fluidsynth setttings for GeneralUser-GS soundfont
    // from: https://github.com/mrbumpy409/GeneralUser-GS/tree/main/documentation#302-fluidsynth
    fluid_settings_setnum(m_fssettings, "synth.reverb.damp", 0.3);
    fluid_settings_setnum(m_fssettings, "synth.reverb.level", 0.7);
    fluid_settings_setnum(m_fssettings, "synth.reverb.room-size", 0.5);
    fluid_settings_setnum(m_fssettings, "synth.reverb.width", 0.8);
    fluid_settings_setnum(m_fssettings, "synth.chorus.depth", 3.6);
    fluid_settings_setnum(m_fssettings, "synth.chorus.level", 0.55);
    fluid_settings_setint(m_fssettings, "synth.chorus.nr", 4);
    fluid_settings_setnum(m_fssettings, "synth.chorus.speed", 0.36);

    m_fsynth = new_fluid_synth(m_fssettings);
    m_fsplayer = new_fluid_player(m_fsynth);
    m_fsaudiodriver = new_fluid_audio_driver(m_fssettings, m_fsynth);
    fluid_synth_sfload(m_fsynth, "GU-GS.sf2", 1);
    fluid_settings_setnum(m_fssettings, "synth.gain", 1);
    fluid_player_set_tick_callback(m_fsplayer, &handlePlayerTick, this);
    //midi sequencing happens in its own thread so we can wait w/o blocking ui input
    m_player.moveToThread(&m_playerthread);
    connect(this, &MIDIController::previewRequested, &m_player, &MIDIPlayer::previewChord);
    connect(this, &MIDIController::playbackRequested, &m_player, &MIDIPlayer::playbackData);
    connect(this, &MIDIController::seekRequested, &m_player, &MIDIPlayer::seek);
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
    if (fluid_player_get_status(m_fsplayer) == FLUID_PLAYER_PLAYING)
        return;
    m_player.interruptPlayback(m_fsplayer);             //runs in main thread
    emit previewRequested(tempchord.chord(), m_fsynth); //runs in playerthread
}
void MIDIController::loadData(const char *data, size_t len) {
    delete_fluid_player(m_fsplayer);
    m_fsplayer = new_fluid_player(m_fsynth);
    fluid_player_set_tick_callback(m_fsplayer, &handlePlayerTick, this);
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

void MIDIController::requestRewind() {
    emit seekRequested(m_fsplayer, 0);
}

void MIDIController::requestSeek(int tick) {
    if (tick < 0)
        return;
    emit seekRequested(m_fsplayer, tick);
}

int MIDIController::handlePlayerTick(void *data, int tick) {
    auto controller = static_cast<MIDIController *>(data);
    emit controller->ticked(tick);
    return FLUID_OK;
}
