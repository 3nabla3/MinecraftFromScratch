#include "pch.h"

#include "Layer2D.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/KeyEvent.h"

Layer2D::Layer2D(const std::string& name)
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
	
	m_Camera = new glm::mat4(glm::perspective(45.0f, 640.0f/480.0f, 0.1f, 150.0f));
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
	UpdatePositions(timestep);
	
	m_BlueTriangle->Use();
	m_Vao->Bind();
	m_IndexBuffer->Bind();
	
	glm::mat4 projection = *m_Camera;
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(m_xPos, m_yPos, m_zPos));
	glm::mat4 rotation = glm::rotate(m_Angle, glm::vec3(0.0f, 1.0f, 0.0f));
	
	m_BlueTriangle->UploadUniformMat4("u_Projection", projection);
	m_BlueTriangle->UploadUniformMat4("u_Translation", translation);
	m_BlueTriangle->UploadUniformMat4("u_Rotation", rotation);

	glClear(GL_COLOR_BUFFER_BIT);
	GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // 6 sides * two triangles per side
}

void Layer2D::OnEvent(Event& e)
{
	// TODO: make the movements smoother
	if (e.GetEventType() == EventType::KeyPressed) {
		KeyPressedEvent& kpe = (KeyPressedEvent&)e;

		if (kpe.GetKeyCode() == GLFW_KEY_A)
			m_Mov.LR = 1;
		if (kpe.GetKeyCode() == GLFW_KEY_D)
			m_Mov.LR = -1;
			
		if (kpe.GetKeyCode() == GLFW_KEY_DOWN)
			m_Mov.UD = 1;
		if (kpe.GetKeyCode() == GLFW_KEY_UP)
			m_Mov.UD = -1;

		if (kpe.GetKeyCode() == GLFW_KEY_W)
			m_Mov.FB = 1;
		if (kpe.GetKeyCode() == GLFW_KEY_S)
			m_Mov.FB = -1;

		if (kpe.GetKeyCode() == GLFW_KEY_LEFT)
			m_Angle += 0.1f;
		if (kpe.GetKeyCode() == GLFW_KEY_RIGHT)
			m_Angle -= 0.1f;
	}
	
	if (e.GetEventType() == EventType::KeyReleased) {
		KeyReleasedEvent& kre = (KeyReleasedEvent&)e;
		if (kre.GetKeyCode() == GLFW_KEY_A || kre.GetKeyCode() == GLFW_KEY_D)
			m_Mov.LR = 0;
		
		if (kre.GetKeyCode() == GLFW_KEY_DOWN || kre.GetKeyCode() == GLFW_KEY_UP)
			m_Mov.UD = 0;

		if (kre.GetKeyCode() == GLFW_KEY_W || kre.GetKeyCode() == GLFW_KEY_S)
			m_Mov.FB = 0;
	}
}


void Layer2D::UpdatePositions(float timestep) {
	m_xPos += timestep * m_Mov.LR * m_MovSpeed;
	m_yPos += timestep * m_Mov.UD * m_MovSpeed;
	m_zPos += timestep * m_Mov.FB * m_MovSpeed;
}