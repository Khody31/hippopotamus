#pragma once

#include "abstract_controller.h"
#include "view.h"

class Controller : public AbstractController {
 public:
  Controller();

  void StartNewGame() override;
  void LoadGame() override;
  void StopGame() override;

  void ContinueGame() override;
  void PauseGame() override;

  void OpenSettings() override;
  void OpenMainMenu() override;
  void OpenGameMenu() override;

  void Close() override;

  void OnKeyPress(QKeyEvent* event) override;
  void OnKeyRelease(QKeyEvent* event) override;

 private:
  View* view;
  bool is_game_on_ = false;
};
