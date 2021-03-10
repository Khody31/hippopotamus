#pragma once

#include <QKeyEvent>
#include <Model/model.h>

#include "abstract_controller.h"
#include "View/view.h"


class Controller : public AbstractController {
 public:
  Controller();

  void LoadRoom() override;
  void StartGame() override;
  void EndGame() override;
  void OnTick() override;
  void LoadMainMenu() override;
  void LoadSettings() override;

 private:
  std::unique_ptr<View> view_ptr_;
  std::unique_ptr<Model> model_ptr_;
};
