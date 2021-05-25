#pragma once

#include <unordered_set>
#include <memory>
#include <vector>
#include <QMouseEvent>

#include "spawner.h"
#include "keyboard.h"
#include "connector.h"
#include "scene.h"

#include "view/media_player.h"

#include "systems/joystick_system.h"
#include "systems/collision_system.h"
#include "systems/movement_system.h"
#include "systems/render_system.h"
#include "systems/serialization_system.h"
#include "systems/death_system.h"
#include "systems/intelligence_system.h"
#include "systems/garbage_system.h"
#include <systems/artifact_system.h>
#include "systems/animation_system.h"
#include "systems/state_system.h"
#include "components/components.h"
#include "view/abstract_controller.h"
#include "utilities/cache.h"

// connecting link between engine and game
class Connector {
 public:
  explicit Connector(QWidget* parent,
                     AbstractController* controller,
                     MediaPlayer* media_player,
                     Cache* cache);

  void OnTick();

  const std::unordered_set<Entity>& GetEntitiesToRender() const;

  void OnKeyPress(Qt::Key key);
  void OnKeyRelease(Qt::Key key);
  void OnMousePress(QMouseEvent* event);

  void StartNewGame();
  void LoadGame();
  void ChangeRoom(DoorComponent door);
  void PlaySound(GameSound::EffectID);

  void GivePlayerBuff(BuffType::Buff buff_type);
  const std::vector<int>& GetPlayerBuff();

  Entity GetPlayer();
  Scene* GetScene();

 private:
  void RegisterComponents();
  void RegisterSystems();

  // `player_` and `coordinator_` must be initialized before `scene_`
  std::unique_ptr<Entity> player_;
  std::unique_ptr<Coordinator> coordinator_;
  std::unique_ptr<Scene> scene_;
  std::unique_ptr<Spawner> spawner_;

  std::unique_ptr<Keyboard> keyboard_;
  MediaPlayer* media_player_;

  std::shared_ptr<RenderSystem> render_system_;
  std::shared_ptr<CollisionSystem> collision_system_;
  std::shared_ptr<JoystickSystem> joystick_system_;
  std::shared_ptr<MovementSystem> movement_system_;
  std::shared_ptr<SerializationSystem> serialization_system_;
  std::shared_ptr<DeathSystem> death_system_;
  std::shared_ptr<IntelligenceSystem> intelligence_system_;
  std::shared_ptr<GarbageSystem> garbage_system_;
  std::shared_ptr<ArtifactSystem> artifact_system_;
  std::shared_ptr<AnimationSystem> animation_system_;
  std::shared_ptr<StateSystem> state_system_;
};
