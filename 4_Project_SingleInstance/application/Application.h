#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "checkError.h"

#include <iostream>

#define app Application::getInstance()

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

private:
    static Application* mInstance;

    GLint mWidth{ 0 };
    GLint mHeight{ 0 };
    GLFWwindow* mWindow{ nullptr };

    Application();
};
