#include "losing_widget.h"

#include "view/buttons/constants.h"

LosingWidget::LosingWidget(AbstractController* controller, QWidget* parent) :
    CustomWidget(controller, parent) {
  back_to_main_menu_button_ = new MenuButton(tr("BACK TO MAIN MENU"), this,
                                             constants::kBackToMainMenu);
  connect(back_to_main_menu_button_, &::QPushButton::clicked, this, [&]() {
    controller_->OpenMainMenu();
  });
}

void LosingWidget::Resize(QSize size) {
  back_to_main_menu_button_->setGeometry
      (back_to_main_menu_button_->CalculateActualPos(size));
}

void LosingWidget::ChangeLanguage(Language language) {
  switch (language) {
    case Language::kEnglish : {
      back_to_main_menu_button_->setText(tr("BACK TO MAIN MENU"));
      break;
    }
    case Language::kRussian : {
      back_to_main_menu_button_->setText(tr("НАЗАД В ГЛАВНОЕ МЕНЮ"));
      break;
    }
    case Language::kBelarusian : {
      back_to_main_menu_button_->setText(tr("НАЗАД Ў ГАЛОЎНАЕ МЕНЮ"));
      break;
    }
  }
}
