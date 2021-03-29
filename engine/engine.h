#ifndef ENGINE_H_
#define ENGINE_H_

class Engine {
 public:
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

  static void Init();

 private:
  Engine() = default;
};

#endif  // ENGINE_H_
