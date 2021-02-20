#include "pch.h"

#include "Window.h"
#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

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

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		WindowData data = *(WindowData*)glfwGetWindowUserPointer(window);
		WindowResizeEvent event(width, height);
		data.EventCallback(event);
	});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		WindowCloseEvent event;
		data.EventCallback(event);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseMovedEvent event((float)x, (float)y);
		data.EventCallback(event);
	});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		switch (action)
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double dx, double dy) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent event((float)dx, (float)dy);
		data.EventCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

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

void Window::SetVSync(bool enable)
{
	glfwSwapInterval(enable ? 1 : 0);
	m_Data.VSync = enable;
}

void Window::EnableCursor(bool enable)
{
	if (enable) glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
