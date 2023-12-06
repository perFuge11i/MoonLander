cmake_minimum_required(VERSION 3.17)
project(MoonLander)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(main main.cpp)
add_executable(tests Test/Tests.cpp)
target_link_libraries(main PRIVATE threepp::threepp imgui::imgui)