#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"

class MenuWidget : public QWidget {
  Q_OBJECT
 public:
  explicit MenuWidget(QWidget* parent = nullptr);
 private:
  QVBoxLayout* main_layout_;
  MenuButton* start_button_;
  MenuButton* settings_button_;
  MenuButton* exit_button_;
};