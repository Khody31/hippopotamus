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
        Engine/Core/game_timer.cpp
        Engine/Core/game_timer.h
        Engine/Components/updatable_on_tick.h
        Engine/Misc/singleton.h
        Engine/Misc/constants.h
        Engine/Components/pixmap_component.h
        Engine/Components/coordinates_base.cpp
        Engine/Components/coordinates_base.h
        Engine/Core/game_scene.h
        Engine/Misc/vector_2d.h
        Engine/Core/game_scene.cpp
        Engine/Components/Interfaces/pixmap_component_interface.h
        Engine/Components/Enums/scene_layer_ids.h
        Engine/Components/Interfaces/updatable_on_tick_interface.h
        Engine/Components/pixmap_component.cpp
        resources/resources.qrc
        Engine/Core/keyboard_interface.cpp Engine/Core/keyboard_interface.h
        Engine/Core/game_object.cpp
        Engine/Core/game_object.h
        main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS Widgets)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
