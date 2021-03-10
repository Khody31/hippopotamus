#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"

class MenuWidget : public QWidget {
  Q_OBJECT
 public:
  explicit MenuWidget(QWidget* parent = nullptr);

  void ConnectStartButton(const std::function<void()>& function_to_connect);
  void ConnectSettingsButton(const std::function<void()>& function_to_connect);
  void ConnectExitButton(const std::function<void()>& function_to_connect);

  void resizeEvent(QResizeEvent* event) override;
 private:
  QVBoxLayout* main_layout_;
  MenuButton* start_button_;
  MenuButton* settings_button_;
  MenuButton* exit_button_;
};