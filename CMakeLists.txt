cmake_minimum_required(VERSION 3.25)
project(rastros)

set(CMAKE_CXX_STANDARD 17)

add_executable(rastros main.cpp Tabuleiro.cpp Tabuleiro.h BitStorage.cpp BitStorage.h procuraRastros.cpp procuraRastros.h)
