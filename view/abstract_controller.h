#pragma once

#include <QKeyEvent>

enum class Language {
  kEnglish,
  kRussian,
  kBelarusian
};

class AbstractController {
 public:
  virtual void LoadGame() = 0;
  virtual void StartNewGame() = 0;
  virtual void OpenSettings() = 0;
  virtual void Close() = 0;
  virtual void OpenMainMenu() = 0;
  virtual void OpenLosingWidget() = 0;
  virtual void OpenWinningWidget() = 0;
  virtual void ContinueGame() = 0;
  virtual void StopGame() = 0;
  virtual void PauseGame() = 0;
  virtual void OpenGameMenu() = 0;
  virtual void OnKeyPress(QKeyEvent* event) = 0;
  virtual void OnKeyRelease(QKeyEvent* event) = 0;
  virtual void ChangeSoundState() = 0;
  virtual void ChangeLanguage(Language language) = 0;
};
