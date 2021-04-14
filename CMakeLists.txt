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
        core/connector.h
        core/game_scene.cpp
        core/game_scene.h
        game_constants.h
        systems/render_system.cpp
        systems/render_system.h
        res/res.qrc)
        engine/component_manager.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or
            -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS Widgets)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
