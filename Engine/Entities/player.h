#pragma once
#include "Engine/Core/game_object.h"
#include "Engine/Components/pixmap_component.h"
#include "Engine/Components/transformation_component_player.h"

class Player : public GameObject {
 public:
  Player();

  void OnTick() override;

};

