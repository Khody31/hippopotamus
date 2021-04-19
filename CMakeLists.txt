cmake_minimum_required(VERSION 3.17)
project(Hippopotamus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

if (APPLE)
    set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/clang_64")
else (APPLE)
    set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/gcc_64/lib/cmake")
endif (APPLE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES engine/entity_manager.cpp
        engine/system_manager.cpp
        engine/coordinator.cpp
        main.cpp
        systems/transformation_system.cpp
        engine/component_manager.cpp
        core/connector.cpp
        core/game_scene.cpp
        systems/render_system.cpp
        res/res.qrc
        view/button_controller.cpp
        view/game.cpp
        view/game_menu.cpp
        view/main_menu.cpp
        view/menu_button.cpp
        view/settings.cpp
        view/view.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Qt${QT_VERSION} COMPONENTS Widgets)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
