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

set(SOURCES Backbone/constants.h
        Backbone/Entity/entity_manager.cpp
        Backbone/Entity/entity_manager.h
        Backbone/Component/component_array_interface.h
        Backbone/Component/component_array.h
        Backbone/Component/component_manager.h
        Backbone/System/game_system.h
        Backbone/System/system_manager.h
        Backbone/System/system_manager.cpp
        Backbone/coordinator.cpp
        Backbone/coordinator.h main.cpp
        Components/components.h
        Systems/transformation_system.cpp
        Systems/transformation_system.h
        Core/game_timer.cpp
        Core/game_timer.h
        game_constants.h
        utils.h
        Core/game_widget.cpp
        Core/game_widget.h)

add_executable(${PROJECT_NAME} ${SOURCES})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS Widgets)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
