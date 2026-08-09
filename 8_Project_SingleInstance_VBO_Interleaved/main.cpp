#include "Application.h"

auto constexpr WINDOW_WIDTH = 800;
auto constexpr WINDOW_HEIGHT = 600;

// 三个顶点坐标
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f};

// 三个顶点颜色
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f};

GLfloat vertices_interleaved[] = {
    // x y z r g b
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

void onResize(int width, int height)
{
    GL_CHECK_ERROR(glViewport(0, 0, width, height));
    std::cout << "onResize: " << width << "x" << height << std::endl;
}

void onkeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// VBO的函数
// VBO的创建和销毁 (一个、一堆)
// VBO就是GPU中内存对象的一个ID编号
void prepareVBO_1()
{
    // 创建一个VBO对象 ***还没有分配显存***
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);

    // 销毁一个VBO对象
    glDeleteBuffers(1, &vbo);

    // 创建一堆VBO对象
    GLuint *vboArray = new GLuint[3];
    glGenBuffers(3, vboArray);

    // 销毁一堆VBO对象
    glDeleteBuffers(3, vboArray);
    delete[] vboArray;
}

void prepareVBO_2()
{
    GLuint vboVertices = 0;

    glGenBuffers(1, &vboVertices);

    // VBO绑定
    // GL_ARRAY_BUFFER: 顶点属性数据
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);

    // VBO填入数据 
    // 向当前绑定的VBO对象分配显存并填入数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vboColors = 0;
    glGenBuffers(1, &vboColors);
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
}

// 为位置和颜色创建两个VBO对象
void prepareVBO_3()
{
    GLuint posVbo = 0;
    GLuint colorVbo = 0;

    glGenBuffers(1, &posVbo);
    glGenBuffers(1, &colorVbo);

    // VBO绑定
    // GL_ARRAY_BUFFER: 顶点属性数据
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // 销毁VBO对象
    glDeleteBuffers(1, &posVbo);
    glDeleteBuffers(1, &colorVbo);
}

// interleaved VBO: 位置和颜色数据交错存储在一个VBO对象中
void prepareVBO_4()
{
    GLuint vboInterleaved = 0;
    glGenBuffers(1, &vboInterleaved);
    glBindBuffer(GL_ARRAY_BUFFER, vboInterleaved);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_interleaved), vertices_interleaved, GL_STATIC_DRAW);
}

int main(int argc, char *argv[], char *envp[])
{
    for (int i = 0; i < argc; ++i)
        std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    if (!app->init(WINDOW_WIDTH, WINDOW_HEIGHT))
        return -1;
    // 设置OpenGL视口以及背景颜色
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    app->setResizeCallBack(onResize);
    app->setKeyCallBack(onkeyCallBack);

    // prepareVBO_1();
    // prepareVBO_2();
    // prepareVBO_3();
    prepareVBO_4();

    // 渲染循环
    while (app->update())
        // 执行OpenGL渲染命令
        GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));

    // delete app;
    app->destroy();
    // app->~Application();
    return 0;
}
