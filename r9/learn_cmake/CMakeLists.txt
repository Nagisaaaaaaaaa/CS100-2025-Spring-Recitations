cmake_minimum_required(VERSION 3.25.2)
project(LearnCMake LANGUAGES CXX)

# if(NOT DEFINED ENV{CPM_SOURCE_CACHE})
set(ENV{CPM_SOURCE_CACHE} "${CMAKE_SOURCE_DIR}/cpm")
# endif()

include(FetchContent)
FetchContent_Declare(
  CPM
  GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake.git
  GIT_TAG v0.40.8
)
FetchContent_MakeAvailable(CPM)

CPMAddPackage(
  NAME glm
  GITHUB_REPOSITORY g-truc/glm
  GIT_TAG 1.0.1
)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
