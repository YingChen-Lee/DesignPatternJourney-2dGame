cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 23)
project(2d_map_game)

set(CMAKE_BUILD_TYPE Debug)

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

add_executable(${PROJECT_NAME} main.cc)

add_subdirectory(domain)
target_link_libraries(${PROJECT_NAME}
                      PUBLIC domain
                      PRIVATE spdlog::spdlog)