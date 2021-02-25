#include "pch.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "Layer2D.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"

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
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(m_xPos, m_yPos, 0.0f));
	glm::mat4 rotation = glm::rotate(m_Angle, glm::vec3(0.0f, 0.0f, 1.0f));
	m_BlueTriangle->UploadUniformMat4("u_Translation", translation);
	m_BlueTriangle->UploadUniformMat4("u_Rotation", rotation);

	glClear(GL_COLOR_BUFFER_BIT);
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
}

void Layer2D::OnEvent(Event& e)
{
	if (e.GetEventType() == EventType::KeyPressed) {
		KeyPressedEvent& kpe = (KeyPressedEvent&)e;

		if (kpe.GetKeyCode() == GLFW_KEY_LEFT)
			m_xPos -= 0.1f;
		if (kpe.GetKeyCode() == GLFW_KEY_RIGHT)
			m_xPos += 0.1f;
		if (kpe.GetKeyCode() == GLFW_KEY_UP)
			m_yPos += 0.1f;
		if (kpe.GetKeyCode() == GLFW_KEY_DOWN)
			m_yPos -= 0.1f;

		if (kpe.GetKeyCode() == GLFW_KEY_LEFT_BRACKET)
			m_Angle += 0.1f;
		if (kpe.GetKeyCode() == GLFW_KEY_RIGHT_BRACKET)
			m_Angle -= 0.1f;
	}
}
