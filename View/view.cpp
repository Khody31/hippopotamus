#include "view.h"
#include "constants.h"

#include <iostream>
#include <QCoreApplication>

View::View(AbstractController* controller) :
    controller_(controller),
    menu_widget_(new MenuWidget(this)),
    game_widget_(new GameWidget(this)),
    settings_widget(new SettingsWidget(this)),
    stacked_widget_(new QStackedWidget(this)) {
  QSizePolicy size_policy(QSizePolicy::Expanding,
                          QSizePolicy::Expanding);

  menu_widget_->setSizePolicy(size_policy);
  game_widget_->setSizePolicy(size_policy);

  stacked_widget_->addWidget(menu_widget_);
  stacked_widget_->addWidget(game_widget_);
  stacked_widget_->addWidget(settings_widget);

  connect(menu_widget_, &::MenuWidget::StartGameEvent, [this]() {
            this->controller_->StartGame();
          });

  connect(menu_widget_, &::MenuWidget::LoadSettingsEvent, [this]() {
    this->controller_->StartGame();
  });

  connect(menu_widget_, &::MenuWidget::ExitEvent, [this]() {
    qApp->quit();
  });

  setMinimumSize(constants::kMinWindowWeight,
                 constants::kMinWindowHeight);
  ShowMainMenu();
  show();
}

void View::ShowMainMenu() {
  stacked_widget_->setCurrentWidget(menu_widget_);
}

void View::ShowGame() {
  stacked_widget_->setCurrentWidget(game_widget_);
}

void View::resizeEvent(QResizeEvent* resize_event) {
  stacked_widget_->setGeometry(QRect(0, 0, width(), height()));
}

void View::ShowSettings() {
  stacked_widget_->setCurrentWidget(settings_widget);
}
