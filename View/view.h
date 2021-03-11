#pragma once

#include <QWidget>
#include <QStackedWidget>

#include "Controller/abstract_controller.h"
#include "game_widget.h"
#include "menu_widget.h"
#include "settings_widget.h"

class View : public QWidget {
  Q_OBJECT
 public:
  explicit View(AbstractController* controller);

  void ShowGame();
  void ShowMainMenu();
  void ShowSettings();

  void resizeEvent(QResizeEvent* resize_event) override;
 private:
  AbstractController* controller_;

  MenuWidget* menu_widget_;
  GameWidget* game_widget_;
  SettingsWidget* settings_widget;
  QStackedWidget* stacked_widget_;
};
