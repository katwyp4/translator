cmake_minimum_required(VERSION 3.23)
project(translator C)

set(CMAKE_C_STANDARD 99)

add_executable(translator main.c translator.c translator.h)
