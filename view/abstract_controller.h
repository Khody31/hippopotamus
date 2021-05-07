#pragma once

#include <QKeyEvent>

class AbstractController {
 public:
  virtual void LoadGame() = 0;
  virtual void StartNewGame() = 0;
  virtual void OpenSettings() = 0;
  virtual void Close() = 0;
  virtual void OpenMainMenu() = 0;
  virtual void ContinueGame() = 0;
  virtual void StopGame() = 0;
  virtual void PauseGame() = 0;
  virtual void OpenGameMenu() = 0;
  virtual void OnKeyPress(QKeyEvent* event) = 0;
  virtual void OnKeyRelease(QKeyEvent* event) = 0;
};
