#pragma once
#include <chrono>
#include "GLFW/glfw3.h"

#include "Window.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
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

	static Application* GetInstance() { return s_Instance; }

private:
	static Application* s_Instance;
	Window* m_Window = nullptr;
	
	bool m_Running = true;
	float m_LastFrameTime;

	VertexArray* m_Vao = nullptr;
	VertexBuffer* m_Buffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexBufferLayout* m_Layout = nullptr;
	Shader* m_BlueTriangle = nullptr;
};

