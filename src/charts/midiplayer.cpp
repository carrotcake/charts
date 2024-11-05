#include "midiplayer.h"
#include <QThread>
using namespace std::chrono_literals;

MIDIPlayer::MIDIPlayer(QObject *parent)
    : QObject{parent} {}

MIDIPlayer::~MIDIPlayer() {}
