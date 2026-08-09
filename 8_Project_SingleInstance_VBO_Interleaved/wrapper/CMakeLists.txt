# 递归便利本文件夹下所有cpp文件放到FUNCS中
file(GLOB_RECURSE WRAPPER ./ *.cpp)

# 将FUNCS中的cpp文件编译成lib库
add_library(wrapper ${WRAPPER})