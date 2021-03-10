#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "menu_button.h"

class MenuWidget : public QWidget {
 Q_OBJECT
 public:
  explicit MenuWidget(QWidget* parent = nullptr);

  void resizeEvent(QResizeEvent* event) override;

  void OnStartButtonClick();
  void OnSettingsButtonClick();
  void OnExitButtonClick();

 signals:
  void StartGameEvent();
  void LoadSettingsEvent();
  void ExitEvent();

 private:
  QVBoxLayout* main_layout_;
  MenuButton* start_button_;
  MenuButton* settings_button_;
  MenuButton* exit_button_;
};