cmake_minimum_required(VERSION 3.15)

project(thh-bgfx-debug LANGUAGES CXX)

find_package(bgfx REQUIRED CONFIG)

include(FetchContent)
FetchContent_Declare(
    as
    GIT_REPOSITORY https://github.com/pr0g/as.git
    GIT_TAG        origin/main)
FetchContent_Declare(
    cmake-helpers
    GIT_REPOSITORY https://github.com/pr0g/cmake-helpers.git
    GIT_TAG        origin/main)
FetchContent_MakeAvailable(as cmake-helpers)

list(APPEND CMAKE_MODULE_PATH ${cmake-helpers_SOURCE_DIR})

add_library(${PROJECT_NAME})
target_sources(
    ${PROJECT_NAME} PRIVATE
    src/debug-line.cpp
    src/debug-circle.cpp
    src/debug-sphere.cpp
    src/debug-quad.cpp
    src/debug-vertex.cpp
    src/debug-shader.cpp)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    bgfx::bgfx
    as)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

target_compile_features(
    ${PROJECT_NAME} PRIVATE cxx_std_17)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<BOOL:${AS_PRECISION_FLOAT}>:AS_PRECISION_FLOAT>
            $<$<BOOL:${AS_PRECISION_DOUBLE}>:AS_PRECISION_DOUBLE>
            $<$<BOOL:${AS_COL_MAJOR}>:AS_COL_MAJOR>
            $<$<BOOL:${AS_ROW_MAJOR}>:AS_ROW_MAJOR>)

include(thh-install)
thh_install_static_with_dependencies(${PROJECT_NAME} thh-bgfx-debug)
