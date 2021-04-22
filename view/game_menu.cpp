#include <QKeyEvent>

#include "game_menu.h"
#include "constants.h"

GameMenuWidget::GameMenuWidget(QWidget* parent,
                               AbstractController* controller) :
    QWidget(parent) {
  controller_ = controller;
  CreateButtons();
  ConnectButtons();
}

void GameMenuWidget::ResumeButtonPressEvent() {
  controller_->ContinueGame();
}

void GameMenuWidget::RestartButtonPressEvent() {
  controller_->StopGame();
  controller_->StartGame();
}

void GameMenuWidget::ToMainMenuButtonPressEvent() {
  controller_->OpenMainMenu();
}

void GameMenuWidget::SoundButtonPressEvent() {
  // TODO(polchernikova): add sound button switching
}

void GameMenuWidget::CreateButtons() {
  resume_button_ =
      new MenuButton(tr("RESUME"), this, menu_constants::kResumeButton);
  restart_button_ =
      new MenuButton(tr("RESTART"), this, menu_constants::kRestartButton);
  sound_button_ =
      new MenuButton(tr("SOUND"), this, menu_constants::kSoundButton);
  to_main_menu_button_ = new MenuButton(tr("TO MAIN MENU"), this,
                                        menu_constants::kToMainMenuButton);
}

void GameMenuWidget::ConnectButtons() {
  connect(restart_button_, &::QPushButton::clicked, this,
          &::GameMenuWidget::RestartButtonPressEvent);
  connect(resume_button_, &::QPushButton::clicked, this,
          &::GameMenuWidget::ResumeButtonPressEvent);
  connect(sound_button_, &::QPushButton::clicked, this,
          &::GameMenuWidget::SoundButtonPressEvent);
  connect(to_main_menu_button_, &::QPushButton::clicked, this,
          &::GameMenuWidget::ToMainMenuButtonPressEvent);
}

void GameMenuWidget::Resize(QSize size) {
  restart_button_->setGeometry(restart_button_->CalculateActualPos(size));
  resume_button_->setGeometry(resume_button_->CalculateActualPos(size));
  sound_button_->setGeometry(sound_button_->CalculateActualPos(size));
  to_main_menu_button_->setGeometry(to_main_menu_button_->CalculateActualPos
      (size));
}

void GameMenuWidget::keyPressEvent(QKeyEvent* event) {
  // ignore event for it to be propagated to parent widget (i.e. Game Widget)
  if (event->key() == Qt::Key_Escape) {
    QWidget::keyPressEvent(event);
  }
  controller_->OnKeyPress(event);
}

void GameMenuWidget::keyReleaseEvent(QKeyEvent* event) {
  controller_->OnKeyRelease(event);
}
