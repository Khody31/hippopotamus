#pragma once

#include <vector>

#include "Controller/abstract_controller.h"
#include "GameObject/player.h"
#include "GameObject/enemy.h"

class Model {
 public:
 private:
  AbstractController* controller_;

  std::vector<Enemy> enemies_;
  std::vector<Player> players_;
};
