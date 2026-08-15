auto constexpr vertexShaderSource = 
"#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"    ourColor = aColor;\n"
"}\0";

auto constexpr fragmentShaderSource =    
"#version 460 core\n"
"in vec3 ourColor;\n    "
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f);\n"
"}\0";