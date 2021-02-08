#include "Application.h"
#include "Core.h"

Application* Application::s_Instance = nullptr;

Application::Application()
	:m_LastFrameTime(0.0f), m_Window(nullptr)
{
	if (Application::s_Instance)
		spdlog::critical("Application already exists");
	
	spdlog::set_level(spdlog::level::level_enum::trace);

	Application::s_Instance = this;
	
	if (!glfwInit())
		return;

	m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		spdlog::error("Failed to initialize Glad");

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			Application::GetInstance()->Close();
		});
}

Application::~Application()
{
	spdlog::trace("Application closed");
}

void Application::Close()
{
	spdlog::trace("Closing application");
	m_Running = false;
}

void Application::OnUpdate(float timestep)
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void Application::Run()
{
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		float ts = time - m_LastFrameTime;
		//spdlog::info("Time step: %f", ts);
		OnUpdate(ts);
		glfwPollEvents();
		m_LastFrameTime = time;
	}
}

Application* Application::GetInstance()
{
	return s_Instance;
}
