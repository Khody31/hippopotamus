#ifndef HIPPOPOTAMUS_GAME_H
#define HIPPOPOTAMUS_GAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "menu_button.h"
#include "abstract_controller.h"

class GameWidget: public QWidget {
 public:
  GameWidget(QWidget* parent, AbstractController* controller);
  void Resize(QSize size);
  void keyPressEvent(QKeyEvent* event);
 private:
  QWidget* game_scene_;
  AbstractController* controller_;
};


#endif //HIPPOPOTAMUS_GAME_H
