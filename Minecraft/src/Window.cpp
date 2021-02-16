#include "pch.h"

#include "Window.h"
#include "Application.h"
#include "Events/KeyEvent.h"

Window::Window(unsigned int width, unsigned int height, const std::string& label)
{
	m_Data.Title = label;
	m_Data.Width = width;
	m_Data.Height = height;

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

	glfwSetWindowUserPointer(m_Window, &m_Data);

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
		// WindowCloseEvent ...
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			spdlog::info("{}", data.Height);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});
}