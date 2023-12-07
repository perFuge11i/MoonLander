cmake_minimum_required(VERSION 3.17)
project(MoonLander)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(main main.cpp
        include/HUD.hpp)
target_link_libraries(main PRIVATE threepp::threepp imgui::imgui)
target_link_libraries(main PRIVATE nlohmann_json nlohmann_json::nlohmann_json)