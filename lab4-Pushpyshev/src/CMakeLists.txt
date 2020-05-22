cmake_minimum_required(VERSION 3.16)
project(lab4 C)
SET(CMAKE_C_FLAGS -pthread)
set(CMAKE_C_STANDARD 11)

add_executable(lab4 main.c)