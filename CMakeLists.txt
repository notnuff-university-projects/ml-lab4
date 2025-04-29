cmake_minimum_required(VERSION 3.16)
project(FuzzyHeaterControl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/notnuff/Qt/6.8.1/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(FuzzyHeaterControl
    main.cpp
    mainwindow.cpp
    mainwindow.h
    fuzzy_logic.cpp
    fuzzy_logic.h
)

target_link_libraries(FuzzyHeaterControl PRIVATE Qt6::Widgets) 