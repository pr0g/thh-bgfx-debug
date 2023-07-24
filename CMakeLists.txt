cmake_minimum_required(VERSION 3.15)

project(thh-bgfx-debug LANGUAGES CXX)

find_package(bgfx REQUIRED CONFIG)

include(FetchContent)
FetchContent_Declare(
  as
  GIT_REPOSITORY https://github.com/pr0g/as.git
  GIT_TAG bda10d818a85b9f7a56de95b41926012344792f8)
FetchContent_Declare(
  cmake-helpers
  GIT_REPOSITORY https://github.com/pr0g/cmake-helpers.git
  GIT_TAG 7e1ded2f027dd2bd3265ab7cb4972d06083fbcc5)
FetchContent_MakeAvailable(as cmake-helpers)

list(APPEND CMAKE_MODULE_PATH ${cmake-helpers_SOURCE_DIR})

add_library(${PROJECT_NAME})
target_sources(
  ${PROJECT_NAME}
  PRIVATE src/debug-line.cpp
          src/debug-cube.cpp
          src/debug-circle.cpp
          src/debug-sphere.cpp
          src/debug-quad.cpp
          src/debug-quad-uv.cpp
          src/debug-quad-uv-dynamic.cpp
          src/debug-vertex.cpp
          src/debug-vertex-uv.cpp
          src/debug-shader.cpp
          src/debug-triangle.cpp)
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(${PROJECT_NAME} PUBLIC bgfx::bgfx bgfx::bx as)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_compile_definitions(
  ${PROJECT_NAME}
  PRIVATE $<$<BOOL:${AS_PRECISION_FLOAT}>:AS_PRECISION_FLOAT>
          $<$<BOOL:${AS_PRECISION_DOUBLE}>:AS_PRECISION_DOUBLE>
          $<$<BOOL:${AS_COL_MAJOR}>:AS_COL_MAJOR>
          $<$<BOOL:${AS_ROW_MAJOR}>:AS_ROW_MAJOR>)

include(thh-install)
thh_install_static_with_dependencies(${PROJECT_NAME} thh-bgfx-debug)
