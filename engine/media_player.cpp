#include "media_player.h"

using namespace GameSound;

void MediaPlayer::PlaySound(EffectID id_in_enum) {
  auto id = static_cast<size_t>(id_in_enum);
  sounds_[id].setVolume(volume_);
  sounds_[id].play();
}

MediaPlayer::MediaPlayer(float volume) : volume_(volume) {
  sounds_[kEnemyHit].setSource(QUrl::fromLocalFile(":/sound/punch.wav"));
}

void MediaPlayer::SetVolume(float volume) {
  volume_ = volume;
}
