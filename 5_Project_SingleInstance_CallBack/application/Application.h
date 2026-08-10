#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "checkError.h"

#include <iostream>

#define app Application::getInstance()

using ResizeCallback = void(*)(int, int);
using keyCallBack = void(*)(GLFWwindow*, int, int, int, int);

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
    void setKeyCallBack(keyCallBack callback);

// 类内函数指针
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    static Application* mInstance;

    GLint mWidth{ 0 };
    GLint mHeight{ 0 };
    GLFWwindow* mWindow{ nullptr };

    ResizeCallback mResizeCallback{ nullptr };
    keyCallBack mKeyCallBack{ nullptr };

    Application();
};
