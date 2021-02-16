#pragma once
#include "GLFW/glfw3.h"
#include <string>

class Window
{
public:
	Window(unsigned int width=640, unsigned int height=480, const std::string& label = std::string("GLFW"));
	~Window();

	GLFWwindow* GetRawWindow() const { return m_Window; }

private:
	GLFWwindow* m_Window;
};

