cmake_minimum_required(VERSION 3.17)
project(Hippopotamus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

if (APPLE)
    set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/clang_64")
else (APPLE)
    set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/gcc_64/lib/cmake")
endif(APPLE)

set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/gcc_64/lib/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
        engine/core/game_timer.cpp
        engine/core/game_timer.h
        engine/components/updatable_on_tick.h
        engine/misc/singleton.h
        engine/misc/constants.h
        engine/components/pixmap_component.h
        engine/core/game_scene.h
        engine/core/game_scene.cpp
        engine/components/interfaces/pixmap_component_interface.h
        engine/components/enums/scene_layer_ids.h
        engine/components/interfaces/updatable_on_tick_interface.h
        engine/components/pixmap_component.cpp
        resources/resources.qrc
        engine/core/keyboard_interface.cpp engine/core/keyboard_interface.h
        engine/core/game_object.cpp
        engine/core/game_object.h
        engine/components/transformation_component_player.cpp
        main.cpp engine/entities/player.cpp
        engine/entities/player.h
        engine/entities/bullet.cpp
        engine/entities/bullet.h
        engine/components/transformation_component_bullet.cpp
        engine/components/transformation_component_bullet.h)

add_executable(${PROJECT_NAME} ${SOURCES})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS Widgets)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
