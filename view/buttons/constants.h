#pragma once

#include <QRect>

namespace constants {

// main menu
constexpr QRect kNewGameButton(35, 20, 30, 10);
constexpr QRect kLoadGameButton(35, 35, 30, 10);
constexpr QRect kSettingsButton(35, 50, 30, 10);
constexpr QRect kExitButton(35, 65, 30, 10);
// game menu
constexpr QRect kResumeButton(35, 20, 30, 10);
constexpr QRect kSoundButton(35, 35, 30, 10);
constexpr QRect kToMainMenuButton(35, 50, 30, 10);
// settings
constexpr QRect kSound(35, 20, 30, 10);
constexpr QRect kToMainMenu(35, 35, 30, 10);
constexpr QRect kEnglish(15, 50, 20, 10);
constexpr QRect kRussian(40, 50, 20, 10);
constexpr QRect kBelarussian(65, 50, 20, 10);

// losing/winning widget
constexpr QRect kBackToMainMenu(35, 80, 30, 10);

}  // namespace constants
