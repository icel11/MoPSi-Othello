cmake_minimum_required(VERSION 3.5)
find_package(Imagine REQUIRED)

project(Othello-Mopsi LANGUAGES CXX)

add_executable(Othello-Mopsi main.cpp
                gamedisplay.h gamedisplay.cpp
                game.h game.cpp)

ImagineUseModules(Othello-Mopsi Graphics)
ImagineUseModules(Othello-Mopsi Images)
