#pragma once

#include <QSoundEffect>

namespace GameSound {
  enum EffectID {
    kEnemyHit,
    kPlayerHit,
    kPlayerDead,
    kPlayerShoot,

    kEnumSize
  };
}  // namespace GameSound

class MediaPlayer {
 public:
  explicit MediaPlayer(float volume);
  void SetVolume(float);
  void PlaySound(GameSound::EffectID);

 private:
  std::array<QSoundEffect, GameSound::kEnumSize> sounds_;
  QSoundEffect background;
  float volume_;
};
