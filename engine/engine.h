#pragma  once

class Engine {
 public:
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

  static void Init();

 private:
  Engine() = default;
};
