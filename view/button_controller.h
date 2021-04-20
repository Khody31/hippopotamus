#ifndef VIEW_BUTTON_CONTROLLER_H_
#define VIEW_BUTTON_CONTROLLER_H_

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
  View* view;
  bool is_game_on_ = false;
};

#endif  // VIEW_BUTTON_CONTROLLER_H_
