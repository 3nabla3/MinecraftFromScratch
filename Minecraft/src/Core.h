#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"
#include "glm/glm.hpp"

#define ASSERT(x) if (!x) spdlog::error("Assertion failed!");
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const std::string& signature, const std::string& filename, int linenumber)
{
	if (GLenum error = glGetError())
		spdlog::error("[OpenGL Error] (%d) %s: %s (%d)", error, signature, filename, linenumber); return true;
	return false;
}