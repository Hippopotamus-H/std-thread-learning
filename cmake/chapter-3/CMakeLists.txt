set(TargetName chapter-3)
project(${TargetName})

if(MSVC)
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT")
endif()

set(TargetPrjDir ${CMAKE_SOURCE_DIR}/src/${TargetName})

list(APPEND SOURCES
${TargetPrjDir}/main.cpp
${TargetPrjDir}/calculatepi.h
${TargetPrjDir}/calculatepi.cpp
)

set(gtestIncludeDir ${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include)


add_executable(${TargetName} ${SOURCES})

# 链接gtest库
target_link_libraries(${TargetName} GTest::gtest GTest::gtest_main)

# 包含目录
target_include_directories(${TargetName} PRIVATE
    ${gtestIncludeDir}
)


