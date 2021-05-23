#include "media_player.h"

void MediaPlayer::PlaySound(GameSound::EffectID id_in_enum) {
  auto id = static_cast<size_t>(id_in_enum);
  sounds_[id].setVolume(volume_);
  sounds_[id].play();
}

MediaPlayer::MediaPlayer(float volume) : volume_(volume) {
  sounds_[GameSound::kEnemyHit].setSource(
      QUrl::fromLocalFile(":/sound/punch.wav"));
  sounds_[GameSound::kPlayerHit].setSource(
      QUrl::fromLocalFile(":/sound/player_hit.wav"));
  sounds_[GameSound::kPlayerDead].setSource(
      QUrl::fromLocalFile(":/sound/player_dead.wav"));
  sounds_[GameSound::kPlayerShoot].setSource(
      QUrl::fromLocalFile(":/sound/shot.wav"));

  background.setSource(QUrl::fromLocalFile(":/sound/background_music.wav"));
  background.setVolume(volume_);
  background.setLoopCount(QSoundEffect::Infinite);
  background.play();
}

void MediaPlayer::SetVolume(float volume) {
  volume_ = volume;
}
