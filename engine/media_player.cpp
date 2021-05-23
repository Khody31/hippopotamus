#include "media_player.h"
#include <QSound>

void MediaPlayer::PlaySound(GameSound::EffectID id_in_enum) {
  QSound::play(sound_to_url.at(id_in_enum));
}

MediaPlayer::MediaPlayer(float volume) : volume_(volume) {
  {
    playlists_[GameSound::kEnemyHit].addMedia(
        QUrl::fromLocalFile(":/sound/punch.wav"));
    playlists_[GameSound::kPlayerHit].addMedia(
        QUrl::fromLocalFile(":/sound/player_hit.wav"));
    playlists_[GameSound::kPlayerDead].addMedia(
        QUrl::fromLocalFile(":/sound/player_dead.wav"));
    playlists_[GameSound::kPlayerShoot].addMedia(
        QUrl::fromLocalFile(":/sound/shot.wav"));
    playlists_[GameSound::kPlayerWon].addMedia(
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
