cmake_minimum_required(VERSION 3.16)
project(std-thread-learning)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置构建类型（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 添加gtest
add_subdirectory(third_party/googletest)


add_subdirectory(cmake/chapter-1)
add_subdirectory(cmake/chapter-2)
add_subdirectory(cmake/chapter-3)