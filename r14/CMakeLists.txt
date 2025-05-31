# 创建一个叫做 CS100-Final 的 CMake 项目。
cmake_minimum_required(VERSION 3.25.2)
project(CS100-Final LANGUAGES CXX)

# 检查是否存在一个叫做 `CPM_SOURCE_CACHE` 的环境变量，
# 如果不存在的话，把它当场定义在“隔壁”。
if(NOT DEFINED ENV{CPM_SOURCE_CACHE})
  set(ENV{CPM_SOURCE_CACHE} "${CMAKE_SOURCE_DIR}/cpm")
endif()

# 下载并导入下方那个 GitHub 仓库 (CPM) 里面的东西。
#
# CPM 是一个“能帮助我们更方便地导入其他库”的工具库。
# 我们使用 CMake 自带的功能来导入 CPM，导入 CPM 之后，
# 我们就拥有了一个叫做 CPMAddPackage 的 CMake 函数。
# 之后，我们将会使用 CPMAddPackage 来导入其他库，它用起来很方便。
include(FetchContent)
FetchContent_Declare(
  CPM
  GIT_REPOSITORY https://github.com/cpm-cmake/CPM.cmake.git
  GIT_TAG v0.42.0
)
FetchContent_MakeAvailable(CPM)

# 下载并导入下方那个 GitHub 仓库 (Arietta) 里面的东西。
#
# 我们使用 CPMAddPackage 来导入 Arietta。
# Arietta 是助教这周偷懒摸鱼临时搓出来的小玩具，
# 它包含了一些 C++ 最诡异的黑魔法，或许作为 "final" 来说正合适。
# 我愿称之为，CS100 最后的魔法！
CPMAddPackage(
  NAME arietta
  GITHUB_REPOSITORY Nagisaaaaaaaaa/arietta
  GIT_TAG main # 你可以永远相信助教的 main branch，我保证它是稳定的。
  OPTIONS "ARIETTA_ENABLE_TESTING OFF" # 我们不需要编译 Arietta 的单元测试。
)

# 创建一个可执行文件。
add_executable(${PROJECT_NAME} main.cpp)

# 链接 Arietta 这个库。
target_link_libraries(${PROJECT_NAME} PUBLIC
  Arietta
)
