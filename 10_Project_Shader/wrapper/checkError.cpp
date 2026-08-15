#include <checkError.h>
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <cassert>

void checkError(void)
{
	auto error = glGetError();
	std::string errorString = "Unknown error";

	if (error != GL_NO_ERROR)
	{
		switch (error)
		{
		case GL_INVALID_ENUM:
			errorString = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorString = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			errorString = "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		default:
			break;
		}
		assert(false);
	}
}