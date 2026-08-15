# 递归便利本文件夹下所有cpp文件放到FUNCS中
file(GLOB_RECURSE WRAPPER ./ *.cpp)

# 将FUNCS中的cpp文件编译成lib库
add_library(wrapper ${WRAPPER})

# 让外部可以找到本模块的头文件
target_include_directories(wrapper
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/thirdParty/include
)