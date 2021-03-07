#pragma once

#include <QKeyEvent>

#include "abstract_controller.h"


class Controller : public AbstractController {
 public:
  void LoadRoom() override;
  void StartGame() override;
  void EndGame() override;
  void OnTick() override;

 private:

};
