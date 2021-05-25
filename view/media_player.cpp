#include <QSound>

#include "view/media_player.h"

void MediaPlayer::PlaySound(GameSound::EffectID id_in_enum) {
  if (!is_enabled_) {
    return;
  }
  players_[id_in_enum].stop();
  players_[id_in_enum].play();
}

MediaPlayer::MediaPlayer(float volume) : volume_(volume), is_enabled_(true) {
  {
    for (size_t i = 0; i < GameSound::kEnumSize; ++i) {
      effects_[i] = QMediaContent(
          QUrl(sound_to_url.at(static_cast<GameSound::EffectID>(i))));
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
  if (!is_enabled_) {
    return;
  }
  if (music_[track_id].isPlaying()) {
    return;
  }
  for (auto& track : music_) {
    track.stop();
  }
  music_[track_id].setVolume(volume_ * 0.6);
  music_[track_id].play();
}

void MediaPlayer::ChangeEnableStatus() {
  float desired_volume = is_enabled_ ? 0.0 : 1.0;
  for (auto& track : music_) {
    track.setVolume(desired_volume * 0.6);
  }
  for (auto& player : players_) {
    player.setVolume(desired_volume);
  }
  is_enabled_ = !is_enabled_;
}

bool MediaPlayer::IsEnabled() const {
  return is_enabled_;
}
