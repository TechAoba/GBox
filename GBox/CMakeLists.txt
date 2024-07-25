## 设置CMake最低版本
cmake_minimum_required(VERSION 3.22)
## 设置项目名称
project(GBOX_LIB)
# 设置编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## 添加include路径
include_directories(include)
include_directories(vendor/spdlog/include)

# 查找所有编译文件
file(GLOB_RECURSE CPP_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# file(GLOB_RECURSE CC_SRC_LIST  ${PROJECT_SOURCE_DIR}/src/*.cc)
# file(GLOB_RECURSE C_SRC_LIST   ${PROJECT_SOURCE_DIR}/src/*.c)
list(APPEND SRC_LIST ${CPP_SRC_LIST}) # ${CC_SRC_LIST} ${C_SRC_LIST}

# 源文件
message("CPP_SRC_LIST=${CPP_SRC_LIST}")

# 查找第三方库
add_subdirectory(vendor/spdlog)

add_definitions(-DNOMINMAX)

## *************** 设置编译参数 ********************
add_library(GBoxLib SHARED ${SRC_LIST})
INSTALL(TARGETS GBoxLib RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(GBoxLib PUBLIC spdlog::spdlog)
