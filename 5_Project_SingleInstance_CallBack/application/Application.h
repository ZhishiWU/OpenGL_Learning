#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "checkError.h"

#include <iostream>

#define app Application::getInstance()

using ResizeCallback = void(*)(int, int);

class Application
{
public:
    ~Application();

    static Application* getInstance();

    bool init(const GLint& mwidth = 800, const GLint& mheight = 600);
    bool update();
    void destroy();

    GLint getWidth() const { return this->mWidth; }
    GLint getHeight() const { return this->mHeight; }

    void setResizeCallBack(ResizeCallback callback);

// 类内函数指针
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
    static Application* mInstance;

    GLint mWidth{ 0 };
    GLint mHeight{ 0 };
    GLFWwindow* mWindow{ nullptr };

    ResizeCallback mResizeCallback{ nullptr };

    Application();
};
