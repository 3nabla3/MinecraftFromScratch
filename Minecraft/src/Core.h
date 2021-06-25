#pragma once

#include <csignal>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"
#include "glm/glm.hpp"

#ifdef _WIN32
#define ASSERT(x) if (!(x)) {spdlog::error("Assertion failed!"); __debugbreak(); }
#elif __linux__
#define ASSERT(x) if (!(x)) {spdlog::error("Assertion failed!"); raise(SIGTRAP); }
#else
#error "OS not supported yet!"
#endif
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const std::string& signature, const std::string& filename, int linenumber)
{
	if (GLenum error = glGetError())
		spdlog::error("[OpenGL Error] {} {}: {} ({})", error, signature, filename, linenumber); return true;
	return false;
}