#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "view/buttons/menu_button.h"
#include "view/abstract_controller.h"
#include "view/widgets/custom_widget.h"

class LosingWidget : public CustomWidget {
 public:
  LosingWidget(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;
  void ChangeLanguage(Language language) override;

 private:
  MenuButton* back_to_main_menu_button_;
};
