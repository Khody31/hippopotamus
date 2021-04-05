#pragma  once

class AbstractKeyboardListener {
 private:
  friend class GameWidget;

  virtual void OnPress(QKeyEvent*) = 0;
  virtual void OnRelease(QKeyEvent*) = 0;
};

