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
