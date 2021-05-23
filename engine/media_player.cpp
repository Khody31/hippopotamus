#include "media_player.h"
#include <QSound>

void MediaPlayer::PlaySound(GameSound::EffectID id_in_enum) {
  players_[id_in_enum].stop();
  players_[id_in_enum].play();
}

MediaPlayer::MediaPlayer(float volume) : volume_(volume) {
  {
    effects_[GameSound::kEnemyHit] = QMediaContent(
        QUrl("qrc:/sound/punch.wav"));
    effects_[GameSound::kPlayerHit] = QMediaContent(
        QUrl("qrc:/sound/player_hit.wav"));
    effects_[GameSound::kPlayerDead] = QMediaContent(
        QUrl("qrc:/sound/player_dead.wav"));
    effects_[GameSound::kPlayerShoot] = QMediaContent(
        QUrl("qrc:/sound/shot.wav"));
    effects_[GameSound::kPlayerWon] = QMediaContent(
        QUrl("qrc:/sound/menu_music.wav"));
    for (size_t i = 0; i < GameSound::kEnumSize; ++i) {
      players_[i].setAudioRole(QAudio::GameRole);
      players_[i].setMedia(effects_[i]);
      players_[i].play();
      players_[i].pause();
    }
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
