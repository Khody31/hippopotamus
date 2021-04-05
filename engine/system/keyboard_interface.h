#pragma  once

#include <QKeyEvent>
#include <unordered_map>

class KeyboardInterface {
 public:
  KeyboardInterface(const KeyboardInterface&) = delete;
  KeyboardInterface& operator=(const KeyboardInterface&) = delete;

  static bool IsPressed(Qt::Key key);
  static bool IsReleased(Qt::Key key);

 private:
  friend class GameWidget;

  KeyboardInterface() = default;

  static KeyboardInterface& Get();

  static void OnPress(Qt::Key key);
  static void OnRelease(Qt::Key key);

  std::unordered_map<Qt::Key, bool> key_states_;
};
