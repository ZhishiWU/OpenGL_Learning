#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <checkError.h>
#include <iostream>

auto constexpr WINDOW_WIDTH = 800;
auto constexpr WINDOW_HEIGHT = 600;

void frambuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// key: GLFW_KEY_*
	// scancode: 平台相关的扫描码
	// action: GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT
	// mods: shift, crtl and so on

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Create window Error!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Loading Error!" << std::endl;
		return -1;
	}

	// 加入窗口大小改变的回调函数
	glfwSetFramebufferSizeCallback(window, frambuffer_size_callback);
	// 加入键盘输入的回调函数
	glfwSetKeyCallback(window, keyCallBack);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 4.0f);

	while (!glfwWindowShouldClose(window))
	{
		GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));

		// 交换缓冲区
		glfwSwapBuffers(window);

		// 接收并分发窗体消息
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
