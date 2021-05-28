#pragma once
#include <chrono>
#include <vector>

#include "GLFW/glfw3.h"

#include "Window.h"
#include "Events/ApplicationEvent.h"

#include "Layer.h"

class Application
{
public:
	Application();
	~Application();

	bool OnWindowClose(WindowCloseEvent& event);
	bool OnWindowResize(WindowResizeEvent& event);
	void OnUpdate(float timestep);
	void OnEvent(Event& e);
	void Run();

	static Application* GetInstance() { return s_Instance; }
	inline const Window* GetWindow() { return m_Window; }

private:
	static Application* s_Instance;
	Window* m_Window = nullptr;
	std::vector<Layer*> m_Layers;
	
	bool m_Running = true;
	float m_LastFrameTime;
};

