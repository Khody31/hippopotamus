#ifndef VIEW_ABSTRACT_CONTROLLER_H_
#define VIEW_ABSTRACT_CONTROLLER_H_

class AbstractController {
 public:
  virtual void StartGame() = 0;
  virtual void OpenSettings() = 0;
  virtual void Close() = 0;
  virtual void OpenMainMenu() = 0;
  virtual void ContinueGame() = 0;
  virtual void StopGame() = 0;
  virtual void PauseGame() = 0;
  virtual void OpenGameMenu() = 0;
 private:
};

#endif  // VIEW_ABSTRACT_CONTROLLER_H_
