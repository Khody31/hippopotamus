#pragma once

#include <memory>

#include <QWidget>
#include <QVBoxLayout>
#include <QKeyEvent>

#include "core/scene.h"
#include "core/connector.h"

#include "view/buttons/menu_button.h"
#include "view/abstract_controller.h"
#include "custom_widget.h"
#include "utilities/cache.h"

class GameWidget : public CustomWidget {
 public:
  GameWidget(AbstractController* controller,
             QWidget* parent,
             MediaPlayer* media_player,
             Cache* cache);
  void Resize(QSize size) override;
  void ChangeLanguage(Language language) override;

  void Continue();
  void Pause();
  void Start();
  void Stop();
  void StartNewGame();

  void OnKeyPress(QKeyEvent* event);
  void OnKeyRelease(QKeyEvent* event);

 private:
  void keyPressEvent(QKeyEvent* event) override;

  std::shared_ptr<Connector> connector_;
  MediaPlayer* media_player_;
  Cache* cache_;
};
