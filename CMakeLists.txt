cmake_minimum_required(VERSION 3.17)
project(Hippopotamus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/gcc_64/lib/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME}
        main.cpp
        GameObject/game_object.cpp
        GameObject/game_object.h
        GameObject/moving_object.cpp
        GameObject/moving_object.h
        GameObject/character.cpp
        GameObject/character.h
        GameObject/player.cpp
        GameObject/player.h
        GameObject/enemy.cpp
        GameObject/enemy.h
        Controller/abstract_controller.cpp
        Controller/abstract_controller.h Controller/controller.cpp Controller/controller.h View/view.cpp View/view.h View/menu_widget.cpp View/menu_widget.h View/game_widget.cpp View/game_widget.h Model/model.cpp Model/model.h)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
