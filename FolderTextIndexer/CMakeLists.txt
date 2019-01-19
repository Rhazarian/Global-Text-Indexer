cmake_minimum_required(VERSION 3.12)
project(GlobalTextIndexer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.11.2/lib/cmake")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_executable(GlobalTextIndexer main.cpp
        action_object.cpp action_object.h
        add_dir_worker.cpp add_dir_worker.h
        add_directory_dialog.cpp add_directory_dialog.h add_directory_dialog.ui
        details_dialog.cpp details_dialog.h details_dialog.ui
        exception_occured_dialog.cpp exception_occured_dialog.h exception_occured_dialog.ui
        main.cpp main_window.cpp main_window.h main_window.ui
        pattern_lookup_worker.cpp pattern_lookup_worker.h trigram_util.h)

target_link_libraries(GlobalTextIndexer Qt5::Core)
target_link_libraries(GlobalTextIndexer Qt5::Gui)
target_link_libraries(GlobalTextIndexer Qt5::Widgets)
target_link_libraries(GlobalTextIndexer stdc++fs)
