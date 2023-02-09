cmake_minimum_required(VERSION 3.5)
find_package(Imagine REQUIRED)

project(Othello-Mopsi LANGUAGES CXX)

add_executable(Othello-Mopsi main.cpp
                display.h display.cpp
                settings.h settings.cpp
                position.h position.cpp
                strategies.h strategies.cpp
                game.h game.cpp)

ImagineUseModules(Othello-Mopsi Graphics)
ImagineUseModules(Othello-Mopsi Images)
