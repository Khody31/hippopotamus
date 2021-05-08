#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"
#include "abstract_controller.h"

class LosingWidget : public QWidget {
 public:
  LosingWidget(QWidget* parent, AbstractController* controller);
  void Resize(QSize size);

 private:
  void CreateButtons();
  void ConnectButtons();
  void BackToMainMenuPressEvent();

  MenuButton* back_to_main_menu_button_;
  AbstractController* controller_;
};
