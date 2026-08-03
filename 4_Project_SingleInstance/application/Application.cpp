#include "Application.h"

Application* Application::mInstance = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Application* Application::getInstance()
{
    if (Application::mInstance == nullptr)
        Application::mInstance = new Application();
    return Application::mInstance;
}

bool Application::init(const GLint& mwidth, const GLint& mheight)
{
    this->mWidth = mwidth;
    this->mHeight = mheight;

    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->mWindow = glfwCreateWindow(mwidth, mheight, "LearnOpenGL", NULL, NULL);

    if (this->mWindow == NULL)
    {
        std::cout << "Create window Error!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(this->mWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Loading GLAD Error!" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetFramebufferSizeCallback(this->mWindow, framebuffer_size_callback);
    glfwSetKeyCallback(this->mWindow, keyCallBack);

    return true;
}

bool Application::update()
{
    if (glfwWindowShouldClose(this->mWindow))
        return false;

    GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));

    glfwSwapBuffers(this->mWindow);
    glfwPollEvents();

    return true;
}

void Application::destroy()
{
    if (this->mWindow)
    {
        glfwDestroyWindow(this->mWindow);
        this->mWindow = nullptr;
    }

    glfwTerminate();
}

Application::Application()
{
    std::cout << "new" << std::endl;
}

Application::~Application()
{}