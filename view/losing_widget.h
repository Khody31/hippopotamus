#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"
#include "abstract_controller.h"
#include "custom_widget.h"

class LosingWidget : public CustomWidget {
 public:
  LosingWidget(AbstractController* controller, QWidget* parent);
  void Resize(QSize size) override;

 private:
  MenuButton* back_to_main_menu_button_;
};
