cmake_minimum_required(VERSION 3.9)
project(TickerValuator)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules/)

find_package(TBB)

include_directories(${TBB_INCLUDE_DIRS})
add_definitions(${TBB_DEFINITIONS})


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -v  -std=c++17 -Wall -Weffc++ -Werror -Wpedantic -Wextra -Wno-deprecated -pedantic -pedantic-errors -O3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -v -std=c++17 -Wall -Weffc++ -Werror -Wpedantic -Wextra -Wno-deprecated -pedantic -pedantic-errors -O3")
add_executable(TickerValuator main.cpp ticker.cpp ticker.h ticker_storage.cpp ticker_storage.h file_manager.h file_manager.cpp simplified_ticker.cpp simplified_ticker.h area_utils.h fmt/format.cc fmt/format.h)

target_link_libraries(TickerValuator ${TBB_LIBRARIES})
