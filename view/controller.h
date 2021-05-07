#pragma once

#include "abstract_controller.h"
#include "view.h"
#include "core/connector.h"

class Controller : public AbstractController {
 public:
  Controller();
  void LoadGame() override;
  void StartNewGame() override;
  void OpenSettings() override;
  void Close() override;
  void OpenMainMenu() override;
  void ContinueGame() override;
  void StopGame() override;
  void PauseGame() override;
  void OpenGameMenu() override;
  void OpenWinningWidget() override;
  void OpenLosingWidget() override;

  void OnKeyPress(QKeyEvent* event) override;
  void OnKeyRelease(QKeyEvent* event) override;

 private:
  View* view;
  bool is_game_on_ = false;
};
