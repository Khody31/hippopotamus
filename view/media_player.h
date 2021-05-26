#pragma once

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <unordered_map>

namespace GameSound {
enum EffectID {
  kEnemyHit,
  kPlayerHit,
  kPlayerDead,
  kPlayerShoot,
  kPlayerWon,
  kFireballSpawn,
  kFireballWallHit,
  kEnterPortal,
  kWand,

  kEnumSize
};
}  // namespace GameSound

namespace GameBackgroundMusic {
enum TrackID {
  kMainMenu,
  kInGame,

  kEnumSize
};
}  // namespace GameBackgroundMusic

class MediaPlayer {
 public:
  explicit MediaPlayer(float volume);
  void SetVolume(float);
  void PlaySound(GameSound::EffectID);
  void SetBackgroundMusic(GameBackgroundMusic::TrackID);

  void ChangeEnableStatus();
  bool IsEnabled() const;

 private:
  std::array<QMediaPlayer, GameSound::kEnumSize> players_;
  std::array<QMediaContent, GameSound::kEnumSize> effects_;
  std::array<QSoundEffect, GameBackgroundMusic::kEnumSize> music_;
  float volume_;

  const std::unordered_map<GameSound::EffectID, QString> sound_to_url{
      {GameSound::kEnemyHit, "qrc:/sound/punch.wav"},
      {GameSound::kPlayerHit, "qrc:/sound/player_hit.wav"},
      {GameSound::kPlayerDead, "qrc:/sound/player_dead.wav"},
      {GameSound::kPlayerShoot, "qrc:/sound/shot.wav"},
      {GameSound::kPlayerWon, "qrc:/sound/win.wav"},
      {GameSound::kFireballSpawn, "qrc:/sound/fireball.wav"},
      {GameSound::kFireballWallHit, "qrc:/sound/fireball_wall_hit.wav"},
      {GameSound::kEnterPortal, "qrc:/sound/enter_portal.wav"},
      {GameSound::kWand, "qrc:/sound/wand.mp3"},
  };

  bool is_enabled_;
};
