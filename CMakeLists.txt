cmake_minimum_required(VERSION 3.17)
project(MoonLander)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(main main.cpp
            include/UI.hpp
            include/AABB.hpp
            include/GJKcomputations.hpp
            include/Landscape.hpp
            include/LunarLanderGame.hpp
            include/MoonScene.hpp
            include/PhysicsEngine.hpp
            include/Spaceship.hpp)

target_link_libraries(main PRIVATE threepp::threepp imgui::imgui)

add_subdirectory(external/Catch2)
add_executable(tests tests/tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

target_include_directories(tests PRIVATE "${CMAKE_SOURCE_DIR}/external/Catch2/src")
target_include_directories(tests PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(tests PRIVATE "${THREEPP_INCLUDE_DIRS}")

target_link_libraries(tests PRIVATE threepp::threepp imgui::imgui)