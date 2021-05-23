#pragma once

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace GameSound {
enum EffectID {
  kEnemyHit,
  kPlayerHit,
  kPlayerDead,
  kPlayerShoot,
  kPlayerWon,

  kEnumSize
};
}  // namespace GameSound

namespace GameBackgroundMusic {
enum TrackID {
  kMainMenu,
  kInGame,

  kEnumSize
};
}

class MediaPlayer {
 public:
  explicit MediaPlayer(float volume);
  void SetVolume(float);
  void PlaySound(GameSound::EffectID);
  void SetBackgroundMusic(GameBackgroundMusic::TrackID);

 private:
  QMediaPlayer sound_;
  std::array<QMediaPlaylist, GameSound::kEnumSize> playlists_;
  std::array<QSoundEffect, GameBackgroundMusic::kEnumSize> music_;
  float volume_;

  const std::unordered_map<GameSound::EffectID, QString> sound_to_url {
      {GameSound::kEnemyHit, ":/sound/punch.wav"},
      {GameSound::kPlayerHit, ":/sound/player_hit.wav"},
      {GameSound::kPlayerDead, ":/sound/player_dead.wav"},
      {GameSound::kPlayerShoot, ":/sound/shot.wav"},
      {GameSound::kPlayerWon, ":/sound/win.wav"},
  };
};
