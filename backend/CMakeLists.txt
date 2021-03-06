cmake_minimum_required(VERSION 3.12.0)

project(LifeCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

include_directories(.)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

function(linkTestLibraries exec)
	target_link_libraries(${exec} gmock ${GTEST_BOTH_LIBRARIES} pthread)
endfunction()

add_subdirectory(app)
add_subdirectory(expression)
add_subdirectory(life)
add_subdirectory(utils)
add_subdirectory(websocket)
