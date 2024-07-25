## 设置CMake最低版本
cmake_minimum_required(VERSION 3.22)
## 设置项目名称
project(Sandbox)
# 设置编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

## 添加include路径
include_directories(include)

# 查找所有编译文件
file(GLOB_RECURSE CPP_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(APPEND SRC_LIST ${CPP_SRC_LIST})

# 源文件
message("CPP_SRC_LIST=${CPP_SRC_LIST}")

# 指定引用的外部库的搜索路径
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)

# 链接库
set(LINK_LIBS
    libGBoxLib.dll
)

add_definitions(-DNOMINMAX)

## *************** 设置编译参数 ********************
## 指定参与编译的源文件
add_executable(Sandbox ${SRC_LIST})
target_link_libraries(Sandbox PUBLIC ${LINK_LIBS})
target_include_directories(Sandbox PUBLIC ${PROJECT_SOURCE_DIR}/../GBox/include)
target_include_directories(Sandbox PUBLIC ${PROJECT_SOURCE_DIR}/../GBox/vendor/spdlog/include)


# 打印所有包含的头文件
get_target_property(my_target_include_dirs Sandbox INCLUDE_DIRECTORIES)
message(STATUS "Include directories for my_target: ${my_target_include_dirs}")