#ifndef HIPPOPOTAMUS_BUTTON_CONTROLLER_H
#define HIPPOPOTAMUS_BUTTON_CONTROLLER_H

#include "abstract_controller.h"
#include "view.h"
#include "core/game_scene.h"
#include "core/connector.h"

class ButtonController : public AbstractController {
 public:
  ButtonController();
  void StartGame() override;
  void OpenSettings() override;
  void Close() override;
  void OpenMainMenu() override;
  void ContinueGame() override;
  void StopGame() override;
  void PauseGame() override;
  void OpenGameMenu() override;
 private:
  View *view;
  bool game_is_on_ = false;
  bool game_is_on_pause_ = false;
};

#endif //HIPPOPOTAMUS_BUTTON_CONTROLLER_H
