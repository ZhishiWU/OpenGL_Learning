#include "Application.h"

auto constexpr WINDOW_WIDTH = 800;
auto constexpr WINDOW_HEIGHT = 600;

int main()
{
    if (!app->init(WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        return -1;
    }

	// 设置OpenGL视口以及背景颜色
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// 渲染循环
    while (app->update())
		// 执行OpenGL渲染命令
        GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));

    app->destroy();
    return 0;
}