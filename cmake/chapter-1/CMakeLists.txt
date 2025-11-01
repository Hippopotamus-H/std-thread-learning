set(TargetName chapter-1)
project(${TargetName})

set(TargetPrjDir ${CMAKE_SOURCE_DIR}/src/chapter-1)

list(APPEND SOURCES
${TargetPrjDir}/main.cpp
)

set(gtestIncludeDir ${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include)


add_executable(${TargetName} ${SOURCES})

# 链接gtest库
target_link_libraries(${TargetName} GTest::gtest GTest::gtest_main)

# 包含目录
target_include_directories(${TargetName} PRIVATE
    ${gtestIncludeDir}
)


