#include "Application.h"

auto constexpr WINDOW_WIDTH = 800;
auto constexpr WINDOW_HEIGHT = 600;

void onResize(int width, int height)
{
    GL_CHECK_ERROR(glViewport(0, 0, width, height));
    std::cout << "onResize: " << width << "x" << height << std::endl;
}

void onkeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char *argv[], char *envp[])
{
    if (!app->init(WINDOW_WIDTH, WINDOW_HEIGHT))
        return -1;

    // 设置OpenGL视口以及背景颜色
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    app->setResizeCallBack(onResize);
    app->setKeyCallBack(onkeyCallBack);

    // 渲染循环 
    while (app->update())
        // 执行OpenGL渲染命令
        GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));

    app->destroy();
    // app->~Application();
    return 0;
}
