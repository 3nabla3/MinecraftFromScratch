#pragma once
#include <chrono>
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "VertexBuffer.h"

class Application
{
public:
	Application();
	~Application();

	void Close();
	void OnUpdate(float timestep);
	void Run();

	static Application* GetInstance();

private:
	GLFWwindow* m_Window;
	static Application* s_Instance;
	bool m_Running = true;
	float m_LastFrameTime;

	VertexBuffer* m_Buffer;
	Shader* m_BlueTriangle;
};

