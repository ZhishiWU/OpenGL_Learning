# 设置编译器编码为utf-8
add_compile_options(/utf-8)

# 最低cmake版本
cmake_minimum_required(VERSION 3.12)

# 工程名称
project(OpenGL_GLFW)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wrapper)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/application)

add_subdirectory(wrapper)
add_subdirectory(application)

# 最低c++标准
set(CMAKE_CXX_STANDARD 17)

# 向项目中增加全局的预编译宏
add_definitions(-DDEBUG)

# 本工程所有cpp文件链接编译器 生成exe可执行文件
add_executable(opengl_glfw "main.cpp" "glad.c")

# include目录
target_include_directories(
	opengl_glfw
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
)

# lib目录
target_link_directories(
	opengl_glfw
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)

# 链接lib库
target_link_libraries(
	opengl_glfw
	glfw3
	wrapper
	app
)
