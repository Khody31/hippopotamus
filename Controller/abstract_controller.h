#pragma once

#include <QObject>
#include <QWidget>

class AbstractController {
 public:
  virtual void LoadRoom() = 0;
  virtual void StartGame() = 0;
  virtual void EndGame() = 0;
  virtual void OnTick() = 0;
};
