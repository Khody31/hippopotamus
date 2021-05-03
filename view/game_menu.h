#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"
#include "abstract_controller.h"

class GameMenuWidget : public QWidget {
 public:
  GameMenuWidget(QWidget* parent, AbstractController* controller);
  void ResumeButtonPressEvent();
  void SoundButtonPressEvent();
  void ToMainMenuButtonPressEvent();
  void Resize(QSize size);

 private:
  void CreateButtons();
  void ConnectButtons();

  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

  MenuButton* resume_button_;
  MenuButton* sound_button_;
  MenuButton* to_main_menu_button_;
  AbstractController* controller_;
};
