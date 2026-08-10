# 递归便利本文件夹下所有cpp文件放到FUNCS中
file(GLOB_RECURSE APP ./ *.cpp)

# 将FUNCS中的cpp文件编译成lib库
add_library(app ${APP})

# 让外部可以找到本模块的头文件
target_include_directories(app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}       # application自己头
        ${CMAKE_SOURCE_DIR}/wrapper       # ✅编译app库自己时，可以找到checkError.h
)

# PUBLIC！因为Application.h对外会include wrapper的头
target_link_libraries(app PUBLIC wrapper)
