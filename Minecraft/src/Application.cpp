#include "pch.h"

#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

#include "Layer2D.h"

#define BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application()
	:m_LastFrameTime(0.0f)
{	
	spdlog::trace("Application was created");
	
	if (s_Instance)
	{
		spdlog::error("Application already exists!");
		return;
	}
	
	s_Instance = this;

	spdlog::trace("Creating window");
	m_Window = new Window();
	m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	spdlog::info(glGetString(GL_VERSION));
	
	m_Layers.push_back(new Layer2D("Layer2d"));

//	float vertices[] = {
//		-0.5f, -0.5f,
//		 0.5f, -0.5f,
//		 0.5f,  0.5f,
//		-0.5f,  0.5f
//	};
//
//	unsigned int indices[6] = {
//		0, 1, 2,
//		2, 3, 0
//	};

//	m_Vao = new VertexArray();
//
//	m_Buffer = new VertexBuffer(vertices, 8 * sizeof(float));
//	m_Buffer->Bind();
//
//	m_Layout = new VertexBufferLayout({
//			{GL_FLOAT, 2, GL_FALSE}
//	});
//
//	m_IndexBuffer = new IndexBuffer(indices, 6);
//
//	m_Vao->AddBuffer(*m_Buffer, *m_Layout);
//
//	m_BlueTriangle = new Shader("res/shaders/shader.glsl");
//	m_BlueTriangle->Use();
}

void Application::OnUpdate(float timestep)
{
	spdlog::trace("Application was updated");
	for (int i = 0; i < m_Layers.size(); i++)
		m_Layers[i]->OnUpdate(timestep);
		
	
	glfwSwapBuffers(m_Window->GetRawWindow());
	glfwPollEvents();
}

void Application::OnEvent(Event& e)
{
	spdlog::trace("Event was captured: {}", e.ToString());
	EventDispacher dispacher(e);
	dispacher.Dispach<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
}

void Application::Run()
{
	spdlog::trace("Application was started");
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		float ts = time - m_LastFrameTime;
		//spdlog::warn("Frame time {}", ts);
		OnUpdate(ts);
		glfwPollEvents();
		m_LastFrameTime = time;
	}
	spdlog::trace("Application was ended");
}

Application::~Application()
{
	spdlog::trace("Application was destroyed");	
	glfwTerminate();
}

bool Application::OnWindowClose(WindowCloseEvent& event)
{
	spdlog::trace("Close button was pressed");
	m_Running = false;
	return true;
}
