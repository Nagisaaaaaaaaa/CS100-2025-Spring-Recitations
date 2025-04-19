cmake_minimum_required(VERSION 3.25.2)
project(LearnCMake LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
          $<TARGET_FILE:${PROJECT_NAME}>
          ${CMAKE_CURRENT_SOURCE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
)
