#pragma once

#include <QRect>

namespace menu_constants {

// main menu
constexpr QRect kNewGameButton = QRect(35, 20, 30, 10);
constexpr QRect kLoadGameButton = QRect(35, 35, 30, 10);
constexpr QRect kSettingsButton = QRect(35, 50, 30, 10);
constexpr QRect kExitButton = QRect(35, 65, 30, 10);
// game menu
constexpr QRect kResumeButton = QRect(35, 20, 30, 10);
constexpr QRect kSoundButton = QRect(35, 35, 30, 10);
constexpr QRect kToMainMenuButton = QRect(35, 50, 30, 10);
// settings
constexpr QRect kSound = QRect(35, 20, 30, 10);
constexpr QRect kToMainMenu = QRect(35, 35, 30, 10);
// losing/winning widget
constexpr QRect kBackToMainMenu = QRect(35, 80, 30, 10);

}  // namespace menu_constants
