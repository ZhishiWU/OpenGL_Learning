#include <Application.h>
#include <shader.hpp>

auto constexpr WINDOW_WIDTH = 800;
auto constexpr WINDOW_HEIGHT = 600;

GLuint vboInterleaved = NULL;
GLuint vao = NULL;

GLint program = NULL;

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
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.95f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.0f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, -0.95f, 0.0f, 0.0f, 1.0f, 1.0f
};

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

void prepareVAO_SingleBuffer()
{
    GLuint posVbo;
    GLuint colorVbo;

    glGenBuffers(1, &posVbo);
    glGenBuffers(1, &colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // 一个VAO存储两个VBO，一个存储位置，一个存储颜色
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, posVbo); // 绑定位置VBO
    glEnableVertexAttribArray(0);          // 启用顶点属性, 必须先激活顶点属性, 才能设置顶点属性指针
    // 设置顶点属性指针
    // glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    // 参数1: 顶点属性位置
    // 参数2: 顶点属性大小 (vec3) 一个属性有几个分量
    // 参数3: 顶点属性类型 每个分量的数据类型
    // 参数4: 是否归一化 (0.0f - 1.0f)
    // 参数5: 步长 (每个顶点属性的字节数, 也就是每个顶点属性占用多少字节)
    // 参数6: 顶点数据的内部偏移量 (相对于第一个顶点属性)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void *)0); // 设置顶点属性指针

    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);                                         // 绑定颜色VBO
    glEnableVertexAttribArray(1);                                                    // 前面已经启用了顶点属性, 现在启用颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void *)0); // 设置顶点属性指针

    glBindVertexArray(NULL); // 解绑VAO
}

void prepareVAO_InterleavedBuffer()
{
    // GLuint vboInterleaved = 0;
    glGenBuffers(1, &vboInterleaved);
    glBindBuffer(GL_ARRAY_BUFFER, vboInterleaved);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_interleaved), vertices_interleaved, GL_STATIC_DRAW);

    // GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));

    glBindVertexArray(NULL);
}

void prepareShader()
{
    // 创建着色器对象
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //检查变量
    GLint success;

    /*
     * glShaderSource: 指定着色器源码
     * 参数1: 着色器对象
     * 参数2: 着色器源码字符串个数
     * 参数3: 着色器源码字符串
     * 参数4: 源码字符串长度 \0结尾的字符串可以不指定长度, 直接传NULL
     */

    // 编译vertexShader着色器
    
    // ShaderFileLoader* shaderLoader = new ShaderFileLoader(".\\shader\\vertexShader.glsl", ".\\shader\\fragmentShader.glsl");

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // 检查着色器是否编译成功
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar *infoLog = new GLchar[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        std::cout << infoLog << std::endl;
        delete[] infoLog;
        return;
    }
    else
        std::cout << "Vertex shader compiled successfully." << std::endl;

    // 编译fragmentShader着色器
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // 检查着色器是否编译成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar *infoLog = new GLchar[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
        std::cout << infoLog << std::endl;
        delete[] infoLog;
        return;
    }
    else
        std::cout << "Fragment shader compiled successfully." << std::endl;

    // GLint vertexShaderProgram;
    // GLint fragmentShaderProgram;

    // 创建着色器程序对象
    program = glCreateProgram();

    // 将着色器对象附加到着色器程序对象
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // 链接着色器程序对象
    glLinkProgram(program);

    // 检查着色器程序是否链接成功
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar *infoLog = new GLchar[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
        std::cout << infoLog << std::endl;
        delete[] infoLog;
    }
    else
        std::cout << "Shader program linked successfully." << std::endl;

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar *infoLog = new GLchar[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
        std::cout << infoLog << std::endl;
        delete[] infoLog;
    }
    else
        std::cout << "Shader program linked successfully." << std::endl;
}

void render()
{
    // 清除颜色缓冲区
    GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));

    // 使用着色器程序对象
    GL_CHECK_ERROR(glUseProgram(program));

    // 绑定VAO对象
    GL_CHECK_ERROR(glBindVertexArray(vao));

    // 绘制三角形
    GL_CHECK_ERROR(glDrawArrays(GL_TRIANGLES, 0, 6));

    // 解绑VAO对象
    GL_CHECK_ERROR(glBindVertexArray(NULL));
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
    // prepareVBO_4();
    // prepareVAO_SingleBuffer();
    prepareVAO_InterleavedBuffer();
    std::cout << "vao = " << vao << " vboInterleaved = " << vboInterleaved <<std::endl;
    prepareShader();
    std::cout << "program = " << program << std::endl;

    // 渲染循环
    while (app->update())
        // 执行OpenGL渲染命令
        // GL_CHECK_ERROR(glClear(GL_COLOR_BUFFER_BIT));
        render();

    // delete app;
    app->destroy();
    // app->~Application();
    return 0;
}
