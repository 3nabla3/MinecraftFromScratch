#include "Application.h"
#include "Core.h"

Application* Application::s_Instance = nullptr;

Application::Application()
	:m_LastFrameTime(0.0f), m_Window(nullptr), m_BlueTriangle(nullptr), m_Buffer(nullptr), m_Layout(nullptr)
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

	float vertices[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	m_Vao = new VertexArray();

	m_Buffer = new VertexBuffer(vertices, 6 * sizeof(float));
	m_Buffer->Bind();

	m_Layout = new VertexBufferLayout({
			{GL_FLOAT, 2, GL_FALSE}
	});

	m_Buffer->SetLayout(m_Layout);

	m_Vao->AddBuffer(*m_Buffer, *m_Layout);

	m_BlueTriangle = new Shader("res/shaders/shader.glsl");
	m_BlueTriangle->Use();
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
		m_Vao->Bind();

		OnUpdate(ts);
		glfwPollEvents();
		m_LastFrameTime = time;
	}
}

Application* Application::GetInstance()
{
	return s_Instance;
}
