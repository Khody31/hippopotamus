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
  std::array<QSoundEffect, GameSound::kEnumSize> sounds_;
  std::array<QSoundEffect, GameBackgroundMusic::kEnumSize> music_;
  float volume_;
};
