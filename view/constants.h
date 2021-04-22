#pragma once

#include <QRect>

namespace menu_constants {

  // game menu
constexpr QRect resume_button = QRect(35, 20, 30, 10);
constexpr QRect restart_button = QRect(35, 35, 30, 10);
constexpr QRect sound_button = QRect(35, 50, 30, 10);
constexpr QRect to_main_menu_button = QRect(35, 65, 30, 10);
  // main menu
constexpr QRect start_game_button = QRect(35, 20, 30, 10);
constexpr QRect settings_button = QRect(35, 35, 30,10);
constexpr QRect exit_button = QRect(35, 50, 30, 10);
  // settings
constexpr QRect sound = QRect(35, 20, 30, 10);
constexpr QRect to_main_menu = QRect(35, 35, 30, 10);

}  // menu_constants