#pragma once

#include <QSoundEffect>

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
  QSoundEffect sound_;
  std::array<QSoundEffect, GameBackgroundMusic::kEnumSize> music_;
  float volume_;

  const std::unordered_map<GameSound::EffectID, QUrl> sound_to_url {
      {GameSound::kEnemyHit, QUrl::fromLocalFile(":/sound/punch.wav")},
      {GameSound::kPlayerHit, QUrl::fromLocalFile(":/sound/player_hit.wav")},
      {GameSound::kPlayerDead, QUrl::fromLocalFile(":/sound/player_dead.wav")},
      {GameSound::kPlayerShoot, QUrl::fromLocalFile(":/sound/shot.wav")},
      {GameSound::kPlayerWon, QUrl::fromLocalFile(":/sound/win.wav")},
  };
};
