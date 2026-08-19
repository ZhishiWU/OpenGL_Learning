#include "Application.h"

Application *Application::mInstance = nullptr;

Application *Application::getInstance()
{
    if (Application::mInstance == nullptr)
        Application::mInstance = new Application();
    return Application::mInstance;
}

bool Application::init(const GLint &mwidth, const GLint &mheight)
{
    this->mWidth = mwidth;
    this->mHeight = mheight;

    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
    glfwSetKeyCallback(this->mWindow, key_callback);

    // this就是当前全局唯一的Application实例
    glfwSetWindowUserPointer(this->mWindow, this);

    return true;
}

bool Application::update()
{
    if (glfwWindowShouldClose(this->mWindow))
        return false;

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
    Application::~Application();
}

void Application::setResizeCallBack(ResizeCallback callback)
{
    this->mResizeCallback = callback;
}

void Application::setKeyCallBack(keyCallBack callback)
{
    this->mKeyCallBack = callback;
}

void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    if (app->mResizeCallback)
    {
        std::cout << "Resize: " << width << "x" << height << std::endl;

        Application *self = static_cast<Application *>(glfwGetWindowUserPointer(window));
        self->mResizeCallback(width, height);
        //    Application::getInstance()->mResizeCallback(width, height);
    }
}

void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (app->mKeyCallBack)
    {
        std::cout << "Key: " << key << ", scancode: " << scancode
                  << ", action: " << action << ", mods: " << mods << std::endl;

        Application *self = static_cast<Application *>(glfwGetWindowUserPointer(window));
        self->mKeyCallBack(window, key, scancode, action, mods);
    }
}

Application::Application()
{
    // std::cout << "new window" << std::endl;
}

Application::~Application()
{
    this->destroy();
    std::cout << "delete" << std::endl;
}