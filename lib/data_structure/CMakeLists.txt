# 定义路径
file(GLOB SRC *.cpp)
# 定义库
add_library(DataStructure STATIC ${SRC})

set(nlohmann_json_DIR "${VCPKG}/installed/x64-windows/share/nlohmann_json")
find_package(nlohmann_json REQUIRED)

# 指定库的头文件目录，供其他目标使用
target_include_directories(DataStructure PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(DataStructure PRIVATE nlohmann_json::nlohmann_json)

# 测试部分
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 引入 Google Test
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    # 添加测试
    enable_testing()
    file(GLOB TEST_SRC test/*.cpp)
    add_executable(DataStructureTest ${TEST_SRC})
    target_link_libraries(DataStructureTest PRIVATE DataStructure nlohmann_json::nlohmann_json gtest gtest_main)
    add_test(NAME DataStructureTest COMMAND DataStructureTest)
endif()