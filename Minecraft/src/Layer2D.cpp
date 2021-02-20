#include "pch.h"

#include "Layer2D.h"
#include "Application.h"

Layer2D::Layer2D(const std::string& name)
	:Layer(name)
{
	spdlog::trace("Layer {} was created", m_DebugName);
	
	float vertices[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	m_Vao = new VertexArray();

	m_Buffer = new VertexBuffer(vertices, 8 * sizeof(float));
	m_Buffer->Bind();

	m_Layout = new VertexBufferLayout({
			{GL_FLOAT, 2, GL_FALSE}
	});

	m_IndexBuffer = new IndexBuffer(indices, 6);

	m_Vao->AddBuffer(*m_Buffer, *m_Layout);

	m_BlueTriangle = new Shader("res/shaders/shader.glsl");
	m_BlueTriangle->Use();
}

Layer2D::~Layer2D()
{
	spdlog::trace("Layer {} was destroyed", m_DebugName);
		
	delete m_Vao;
	delete m_Buffer;
	delete m_IndexBuffer;
	delete m_Layout;
	delete m_BlueTriangle;
}

void Layer2D::OnAttach()
{
	spdlog::trace("Layer {} was attached", m_DebugName);
}

void Layer2D::OnDetach()
{
	spdlog::trace("Layer {} was detached", m_DebugName);

}

void Layer2D::OnUpdate(float timestep)
{
	m_BlueTriangle->Use();
	m_Vao->Bind();
	m_IndexBuffer->Bind();
	
	glClear(GL_COLOR_BUFFER_BIT);
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Layer2D::OnEvent(Event& e)
{
}
