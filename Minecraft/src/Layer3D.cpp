#include "pch.h"

#include "Layer3D.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

Layer3D::Layer3D(const std::string& name)
	:Layer(name)
{
	spdlog::trace("Layer {} was created", m_DebugName);
	
	float vertices[] = {
//		-0.5f, -0.5f,
//		 0.5f, -0.5f,
//		 0.5f,  0.5f,
//		-0.5f,  0.5f
		0.0f,  0.0f,  0.0f, // 0
		0.0f,  0.0f,  1.0f, // 1
		0.0f,  1.0f,  0.0f, // 2
		0.0f,  1.0f,  1.0f, // 3 
	
		1.0f,  0.0f,  0.0f, // 4
		1.0f,  0.0f,  1.0f, // 5
		1.0f,  1.0f,  0.0f, // 6
		1.0f,  1.0f,  1.0f, // 7
	};

	unsigned int indices /* of a cube */ [] = {
		// sides that touch the origin
		0, 2, 4, 2, 4, 6,
		0, 2, 1, 2, 1, 3,
		0, 4, 1, 4, 1, 5,
		
		// sides that do not touch the origin
		7, 6, 3, 6, 3, 2,
		7, 6, 5, 6, 5, 4,
		7, 3, 5, 3, 5, 1
	};

	m_Vao = new VertexArray();

	m_Buffer = new VertexBuffer(vertices, 8 * 3 * sizeof(float));
	m_Buffer->Bind();

	m_Layout = new VertexBufferLayout({
			{GL_FLOAT, 3, GL_FALSE}
	});

	m_IndexBuffer = new IndexBuffer(indices, 6 * 6);

	m_Vao->AddBuffer(*m_Buffer, *m_Layout);

	m_BlueTriangle = new Shader("res/shaders/shader.glsl");
	m_BlueTriangle->Use();
	
	m_Projection = new glm::mat4(glm::perspective(45.0f, 640.0f/480.0f, 0.1f, 150.0f));
}

Layer3D::~Layer3D()
{
	spdlog::trace("Layer {} was destroyed", m_DebugName);
		
	delete m_Vao;
	delete m_Buffer;
	delete m_IndexBuffer;
	delete m_Layout;
	delete m_BlueTriangle;
}


void Layer3D::OnAttach()
{
	spdlog::trace("Layer {} was attached", m_DebugName);
}

void Layer3D::OnDetach()
{
	spdlog::trace("Layer {} was detached", m_DebugName);

}

void Layer3D::OnUpdate(float timestep)
{
	UpdatePositions(timestep);
	
	m_BlueTriangle->Use();
	m_Vao->Bind();
	m_IndexBuffer->Bind();
	
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), m_Pos);
	glm::mat4 rotation = glm::rotate(m_Angle.y, glm::vec3(1.0f, 0.0f, 0.0f));
	rotation = glm::rotate(rotation, m_Angle.x, glm::vec3(0.0f, 1.0f, 0.0f));
	
	m_BlueTriangle->UploadUniformMat4("u_Projection", *m_Projection);
	m_BlueTriangle->UploadUniformMat4("u_Translation", translation);
	m_BlueTriangle->UploadUniformMat4("u_Rotation", rotation);

	glClear(GL_COLOR_BUFFER_BIT);
	GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // 6 sides * two triangles per side
}

void Layer3D::OnEvent(Event& e)
{
	if (e.GetEventType() == EventType::MouseMoved) {
		MouseMovedEvent& mme = (MouseMovedEvent&)e;
		
		glm::vec2 currentPos = glm::vec2(mme.GetX(), mme.GetY());
		glm::vec2 delta = currentPos - m_PrevMousePos;
		
		// do not take the mouse position into account on the first frame
		if (m_PrevMousePos.x != -1.f)
			m_Angle.x += delta.x * m_AngleSpeed;
		if (m_PrevMousePos.x != -1.f)
			m_Angle.y += delta.y * m_AngleSpeed;
			
		spdlog::info("{}, {}", delta.x, delta.y);
		m_PrevMousePos = currentPos;
	}
	
	if (e.GetEventType() == EventType::KeyPressed) {
		KeyPressedEvent& kpe = (KeyPressedEvent&)e;
		
		switch (kpe.GetKeyCode()) {
			case GLFW_KEY_A:			
				m_Mov.LR = 1;
				break;
			case GLFW_KEY_D:
				m_Mov.LR = -1;
				break;
			
			case GLFW_KEY_LEFT_SHIFT:			
				m_Mov.UD = 1;
				break;
			case GLFW_KEY_SPACE:
				m_Mov.UD = -1;
				break;
				
			case GLFW_KEY_W:			
				m_Mov.FB = 1;
				break;
			case GLFW_KEY_S:
				m_Mov.FB = -1;
				break;
			
		}
		
	}
	
	if (e.GetEventType() == EventType::KeyReleased) {
		KeyReleasedEvent& kre = (KeyReleasedEvent&)e;
		
		switch (kre.GetKeyCode()) {
			case GLFW_KEY_A:
			case GLFW_KEY_D:
				m_Mov.LR = 0;
				break;
			case GLFW_KEY_LEFT_SHIFT:
			case GLFW_KEY_SPACE:
				m_Mov.UD = 0;
				break;
			case GLFW_KEY_W:
			case GLFW_KEY_S:
				m_Mov.FB = 0;
				break;
		}

	}
}


void Layer3D::UpdatePositions(float timestep) {
	m_Pos.x += timestep * m_Mov.LR * m_MovSpeed * glm::cos(m_Angle.x);
	m_Pos.z += timestep * m_Mov.LR * m_MovSpeed * glm::sin(m_Angle.x);

	m_Pos.y += timestep * m_Mov.UD * m_MovSpeed;

	m_Pos.z += timestep * m_Mov.FB * m_MovSpeed * glm::cos(m_Angle.x);
	m_Pos.x -= timestep * m_Mov.FB * m_MovSpeed * glm::sin(m_Angle.x);
}