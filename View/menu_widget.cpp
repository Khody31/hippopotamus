#include "menu_widget.h"

MenuWidget::MenuWidget(QWidget* parent) :
    QWidget(parent),
    main_layout_(new QVBoxLayout(this)),
    start_button_(new MenuButton("Start", this)),
    settings_button_(new MenuButton("Settings", this)),
    exit_button_(new MenuButton("Exit", this)) {
  main_layout_->addWidget(start_button_);
  main_layout_->addWidget(settings_button_);
  main_layout_->addWidget(exit_button_);
}

void MenuWidget::resizeEvent(QResizeEvent* event) {
  main_layout_->setGeometry(QRect(0, 0, width(), height()));
}
void MenuWidget::ConnectStartButton(const std::function<void()>& function_to_connect) {
  connect(start_button_, &::MenuButton::clicked, function_to_connect);
}

void MenuWidget::ConnectSettingsButton(const std::function<void()>& function_to_connect) {
  connect(settings_button_, &::MenuButton::clicked, function_to_connect);
}

void MenuWidget::ConnectExitButton(const std::function<void()>& function_to_connect) {
  connect(settings_button_, &::MenuButton::clicked, function_to_connect);
}
