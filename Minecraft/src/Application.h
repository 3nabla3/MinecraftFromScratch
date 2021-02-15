#pragma once
#include <chrono>
#include "GLFW/glfw3.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

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

	VertexArray* m_Vao;
	VertexBuffer* m_Buffer;
	VertexBufferLayout* m_Layout;
	Shader* m_BlueTriangle;
};

