#ifndef ABSTRACT_KEYBOARD_LISTENER_H_
#define ABSTRACT_KEYBOARD_LISTENER_H_

class AbstractKeyboardListener {
 private:
  friend class GameWidget;

  virtual void OnPress(QKeyEvent*) = 0;
  virtual void OnRelease(QKeyEvent*) = 0;
};

#endif  // ABSTRACT_KEYBOARD_LISTENER_H_
