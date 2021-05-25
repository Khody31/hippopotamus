#include "view.h"

View::View(AbstractController* controller) :
    media_player_(std::make_unique<MediaPlayer>(1.0)),
    game_widget_(new GameWidget(controller, this,
                                media_player_.get(), cache_.get())),
    game_menu_(new GameMenu(controller, this)),
    main_menu_(new MainMenu(controller, this)),
    settings_menu_(new SettingsMenu(controller, this)),
    losing_widget_(new LosingWidget(controller, this)),
    winning_widget_(new WinningWidget(controller, this)),
    cache_(std::make_unique<Cache>()) {
  addWidget(main_menu_);
  addWidget(settings_menu_);
  addWidget(game_widget_);
  addWidget(game_menu_);
  addWidget(losing_widget_);
  addWidget(winning_widget_);

  QPixmap pixmap(":textures/cursor.png");
  QCursor cursor(pixmap, 0, 0);
  setCursor(cursor);

  SwitchToMainMenu();
  resize(1600, 900);
}

void View::SwitchToGame() {
  game_widget_->Resize(size());
  setCurrentWidget(game_widget_);
  media_player_->SetBackgroundMusic(GameBackgroundMusic::kInGame);
}

void View::SwitchToGameMenu() {
  setCurrentWidget(game_menu_);
  media_player_->SetBackgroundMusic(GameBackgroundMusic::kMainMenu);
}

void View::SwitchToMainMenu() {
  setCurrentWidget(main_menu_);
  media_player_->SetBackgroundMusic(GameBackgroundMusic::kMainMenu);
}

void View::SwitchToSettings() {
  setCurrentWidget(settings_menu_);
  media_player_->SetBackgroundMusic(GameBackgroundMusic::kMainMenu);
}

void View::SwitchToLosingWidget() {
  setCurrentWidget(losing_widget_);
  media_player_->SetBackgroundMusic(GameBackgroundMusic::kMainMenu);
}

void View::SwitchToWinningWidget() {
  setCurrentWidget(winning_widget_);
  media_player_->SetBackgroundMusic(GameBackgroundMusic::kMainMenu);
}
void View::resizeEvent(QResizeEvent* event) {
  QSize new_size = size();
  resize(new_size);
  game_widget_->Resize(new_size);
  game_menu_->Resize(new_size);
  main_menu_->Resize(new_size);
  losing_widget_->Resize(new_size);
  winning_widget_->Resize(new_size);
  settings_menu_->Resize(new_size);
}

void View::ContinueGame() {
  game_widget_->Continue();
}

void View::PauseGame() {
  game_widget_->Pause();
}

void View::StartGame() {
  game_widget_->Start();
}

void View::StartNewGame() {
  game_widget_->StartNewGame();
}

void View::StopGame() {
  game_widget_->Stop();
}

void View::OnKeyPress(QKeyEvent* event) {
  game_widget_->OnKeyPress(event);
}

void View::OnKeyRelease(QKeyEvent* event) {
  game_widget_->OnKeyRelease(event);
}

void View::ChangeSoundState(Language current_language) {
  media_player_->ChangeEnableStatus();
  settings_menu_->ChangeSoundLabel(media_player_->IsEnabled(),
                                   current_language);
  game_menu_->ChangeSoundLabel(media_player_->IsEnabled(), current_language);
}

void View::ChangeLanguage(Language language) {
  main_menu_->ChangeLanguage(language);
  settings_menu_->ChangeLanguage(language);
  game_menu_->ChangeLanguage(language);
  game_widget_->ChangeLanguage(language);
  losing_widget_->ChangeLanguage(language);
  winning_widget_->ChangeLanguage(language);

  settings_menu_->ChangeSoundLabel(media_player_->IsEnabled(), language);
  game_menu_->ChangeSoundLabel(media_player_->IsEnabled(), language);
}
