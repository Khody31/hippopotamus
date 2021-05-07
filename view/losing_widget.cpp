#include "losing_widget.h"
#include "constants.h"

LosingWidget::LosingWidget(QWidget* parent, AbstractController* controller) :
    QWidget(parent) {
  controller_ = controller;
  CreateButtons();
  ConnectButtons();
}

void LosingWidget::BackToMainMenuPressEvent() {
  controller_->OpenMainMenu();
}

void LosingWidget::CreateButtons() {
  back_to_main_menu_button_ = new MenuButton(tr("BACK TO MAIN MENU"), this,
                                             menu_constants::kBackToMainMenu);
}

void LosingWidget::ConnectButtons() {
  connect(back_to_main_menu_button_, &::QPushButton::clicked, this,
          &::LosingWidget::BackToMainMenuPressEvent);
}

void LosingWidget::Resize(QSize size) {
  back_to_main_menu_button_->setGeometry
      (back_to_main_menu_button_->CalculateActualPos(size));
}



