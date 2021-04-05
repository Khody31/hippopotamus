#pragma  once

#include <QKeyEvent>
#include <unordered_map>

class KeyboardInterface {
 public:
  KeyboardInterface(const KeyboardInterface&) = delete;
  KeyboardInterface& operator=(const KeyboardInterface&) = delete;

  static bool IsPressed(quint32 key_code);
  static bool IsReleased(quint32 key_code);

 private:
  friend class GameWidget;

  KeyboardInterface() = default;

  static KeyboardInterface& Get();

  static void OnPress(quint32 key_code);
  static void OnRelease(quint32 key_code);

  std::unordered_map<int, bool> key_states_;
};
