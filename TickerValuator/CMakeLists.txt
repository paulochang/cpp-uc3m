cmake_minimum_required(VERSION 3.9)
project(TickerValuator)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v -Wall -Weffc++ -Werror -Wpedantic -Wextra -Wno-deprecated -pedantic -pedantic-errors")
add_executable(TickerValuator main.cpp ticker.cpp ticker.h)