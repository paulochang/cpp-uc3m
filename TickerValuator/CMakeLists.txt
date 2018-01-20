cmake_minimum_required(VERSION 3.9)
project(TickerValuator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -v -Wall -Weffc++ -Werror -Wpedantic -Wextra -Wno-deprecated -pedantic -pedantic-errors -O3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -v -Wall -Weffc++ -Werror -Wpedantic -Wextra -Wno-deprecated -pedantic -pedantic-errors -O3")
add_executable(TickerValuator main.cpp ticker.cpp ticker.h ticker_storage.cpp ticker_storage.h file_manager.h file_manager.cpp simplified_ticker.cpp simplified_ticker.h area_utils.h)
add_executable(InputTest input.cpp ticker.cpp ticker.h ticker_storage.cpp ticker_storage.h file_manager.h file_manager.cpp simplified_ticker.cpp simplified_ticker.h area_utils.h)
