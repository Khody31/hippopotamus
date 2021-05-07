#include "winning_widget.h"
#include "constants.h"

WinningWidget::WinningWidget(QWidget* parent, AbstractController* controller) :
    QWidget(parent) {
  controller_ = controller;
  CreateButtons();
  ConnectButtons();
}

void WinningWidget::BackToMainMenuPressEvent() {
  controller_->OpenMainMenu();
}

void WinningWidget::CreateButtons() {
  back_to_main_menu_button_ = new MenuButton(tr("BACK TO MAIN MENU"), this,
                                             menu_constants::kBackToMainMenu);
}

void WinningWidget::ConnectButtons() {
  connect(back_to_main_menu_button_, &::QPushButton::clicked, this,
          &::WinningWidget::BackToMainMenuPressEvent);
}

void WinningWidget::Resize(QSize size) {
  back_to_main_menu_button_->setGeometry
      (back_to_main_menu_button_->CalculateActualPos(size));
}

