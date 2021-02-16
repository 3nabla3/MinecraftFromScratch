#include "pch.h"

#include "Window.h"
#include "Application.h"

Window::Window(unsigned int width, unsigned int height, const std::string& label)
{
	if (!glfwInit())
	{
		spdlog::error("GLFW failed to intialize!");
		return;
	}

	m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

	if (!m_Window)
	{
		spdlog::error("GLFW failed to intialize!");
		glfwTerminate();
		return;
	}
	
	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		spdlog::error("Failed to initialize Glad");

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		Application::GetInstance()->Close();
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			
		});
}