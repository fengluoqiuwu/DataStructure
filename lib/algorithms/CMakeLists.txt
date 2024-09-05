# 定义路径
file(GLOB SRC *.cpp)
# 定义库
add_library(Algorithms STATIC ${SRC})

set(nlohmann_json_DIR "${VCPKG}/installed/x64-windows/share/nlohmann_json")
find_package(nlohmann_json REQUIRED)

# 指定库的头文件目录，供其他目标使用
target_include_directories(Algorithms PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Algorithms PRIVATE nlohmann_json::nlohmann_json)

# 测试部分
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 引入 Google Test
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    # 添加测试
    enable_testing()
    file(GLOB TEST_SRC test/*.cpp)
    add_executable(AlgorithmsTest ${TEST_SRC})
    target_link_libraries(AlgorithmsTest PRIVATE Algorithms GTest::GTest GTest::Main)
    add_test(NAME AlgorithmsTest COMMAND AlgorithmsTest)
endif()