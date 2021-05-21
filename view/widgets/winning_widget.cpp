#include "winning_widget.h"
#include "view/buttons/constants.h"

WinningWidget::WinningWidget(AbstractController* controller, QWidget* parent) :
    CustomWidget(controller, parent) {
  back_to_main_menu_button_ = new MenuButton(tr("BACK TO MAIN MENU"), this,
                                             constants::kBackToMainMenu);
  connect(back_to_main_menu_button_, &::QPushButton::clicked, this, [&]() {
    controller_->OpenMainMenu();
  });
}

void WinningWidget::Resize(QSize size) {
  back_to_main_menu_button_->setGeometry
      (back_to_main_menu_button_->CalculateActualPos(size));
}
