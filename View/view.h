#pragma once

#include <QWidget>
#include <QStackedWidget>

#include "Controller/abstract_controller.h"
#include "game_widget.h"
#include "menu_widget.h"

class View : public QWidget {
  explicit View(AbstractController* controller);


 private:
  AbstractController* controller_;

  MenuWidget* menu_;
  GameWidget* game_;
  QStackedWidget* stacked_widget_;
};