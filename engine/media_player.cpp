#include "media_player.h"

void MediaPlayer::PlaySound(GameSound::EffectID id_in_enum) {
  auto id = static_cast<size_t>(id_in_enum);
  sounds_[id].setVolume(volume_);
  sounds_[id].play();
}

MediaPlayer::MediaPlayer(float volume) : volume_(volume) {
  {
    sounds_[GameSound::kEnemyHit].setSource(
        QUrl::fromLocalFile(":/sound/punch.wav"));
    sounds_[GameSound::kPlayerHit].setSource(
        QUrl::fromLocalFile(":/sound/player_hit.wav"));
    sounds_[GameSound::kPlayerDead].setSource(
        QUrl::fromLocalFile(":/sound/player_dead.wav"));
    sounds_[GameSound::kPlayerShoot].setSource(
        QUrl::fromLocalFile(":/sound/shot.wav"));
    sounds_[GameSound::kPlayerWon].setSource(
        QUrl::fromLocalFile(":/sound/win.wav"));
  }

  {
    music_[GameBackgroundMusic::kInGame].setSource(QUrl::fromLocalFile(
        ":/sound/background_music.wav"));
    music_[GameBackgroundMusic::kMainMenu].setSource(QUrl::fromLocalFile(
        ":/sound/menu_music.wav"));
    for (auto& track : music_) {
      track.setLoopCount(QSoundEffect::Infinite);
    }
  }
}

void MediaPlayer::SetVolume(float volume) {
  volume_ = volume;
}

void MediaPlayer::SetBackgroundMusic(GameBackgroundMusic::TrackID track_id) {
  if (music_[track_id].isPlaying()) {
    return;
  }
  for (auto& track : music_) {
    track.stop();
  }
  music_[track_id].setVolume(volume_ * 0.6);
  music_[track_id].play();
}
