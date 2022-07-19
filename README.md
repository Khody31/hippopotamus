# Hippopotamus

**Hippopotamus** is a non-comercial 2D rogue-like game written in C++ using the [Qt Framework](https://www.qt.io) and Entity Component System architechture pattern.

The game is a study project of FAMCS BSU first year students (February - May 2021) 

Team members:

* Yahor Khadasevich ([@Khody31](https://github.com/Khody31))
* Palina Chernikava ([@polchernikova](https://github.com/polchernikova))
* Mikalai Hapaniaka ([@NikolaiNick](https://github.com/NikolaiNick))
* Uladzislau Koshchanka ([@Koshchanka](https://github.com/Koshchanka))

Mentors:

* Maxim Miasoedenkov([@ternerss](https://github.com/ternerss))
* Uladzimir Kuzmitsky([@VKuzia](https://github.com/VKuzia))

Best illustrator in the world:

* German Nester([@Xijiks](https://github.com/Xijiks))

## Game Description

The main character of the game is a traveler who mysteriously found
himself in an ancient dungeon. Now he must survive, find and defeat all the bosses. 

| ![](resources/preview/gameplay.png) |
| ---------------------------------- |

| ![](resources/preview/boss-figth.png) | 
| ---------------------------------- |

## Development status

Development started in March 2021 and completed in May 2021.
In releases you can find executable files with which you can run the game on 64-bit Windows. You can also clone this repo and compile the project on any OS.

## Continuous integration

The automatic build and static analysis is started after each commit. This usually takes up to two minutes. The result can be viewed on the [GitHub Actions page](https://github.com/Khody31/hippopotamus/actions) or in the commit status. 

Cppcheck notes don't change the build status, but it is recommended to read an fix them
if necessary. 'Cpplint' warnings and build erros must not be ignored.

## Building project with CMake

If you want to work with the project in CLion, you need to clone the repository. 
Then you need to edit the file *CMakeLists.txt*.
Add the line describing the path to CMake config files contained in Qt.
For example:

 `set(CMAKE_PREFIX_PATH "~/Qt/5.15.2/gcc_64/lib/cmake)` for Linux 
 
 `set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.13.0/5.13.0/mingw73_64/lib/cmake")` for Windows

If your OS is Linux, work is done. Otherwise you have to add path to Qt libraries and compiler into *Path*.
For exmample:

`C:\Qt\Tools\mingw810_64\bin`

`C:\Qt\5.15.2\mingw81_64\bin`

After that you need to reboot your Windows. 
