#include "pch.h"

#include "Application.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

#include "Layer3D.h"

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
	m_Window = new Window("Minecraft", 1000, 1000);
	m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	spdlog::info("Version:");
	spdlog::info("\t {}", glGetString(GL_VERSION));
	spdlog::info("Vendor:");
	spdlog::info("\t {}", glGetString(GL_VENDOR));
	spdlog::info("Renderer:");
	spdlog::info("\t {}", glGetString(GL_RENDERER));

	m_Window->SetVSync(false);
	m_Window->EnableCursor(false);
	
	m_Layers.push_back(new Layer3D("Layer2d"));

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST); // makes the objects in the back render before the objects in the front
}

void Application::OnUpdate(float timestep)
{
	for (int i = 0; i < m_Layers.size(); i++)
		m_Layers[i]->OnUpdate(timestep);
		
	glfwSwapBuffers(m_Window->GetRawWindow());
	glfwPollEvents();
}

void Application::OnEvent(Event& e)
{
	if (e.GetEventType() == EventType::KeyPressed) {
		KeyPressedEvent& kpe = (KeyPressedEvent&)e;
		
		switch (kpe.GetKeyCode()) {
			case GLFW_KEY_ESCAPE:
			{
				bool prevState = m_Window->IsCursorEnabled();
				m_Window->EnableCursor(!prevState);
				break;
			}
			case GLFW_KEY_F1:
				m_Running = false;
				break;
		}
		
	}
	EventDispacher dispacher(e);
	dispacher.Dispach<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

	for (int i = 0; i < m_Layers.size(); i++) {
		m_Layers.at(i)->OnEvent(e);
	}
}

void Application::Run()
{
	spdlog::trace("Application was started");
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		float ts = time - m_LastFrameTime;
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