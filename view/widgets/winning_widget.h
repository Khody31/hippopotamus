#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "view/buttons/menu_button.h"
#include "view/controller/abstract_controller.h"
#include "view/widgets/custom_widget.h"

class WinningWidget : public CustomWidget {
 public:
  WinningWidget(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;

 private:
  MenuButton* back_to_main_menu_button_;
};
