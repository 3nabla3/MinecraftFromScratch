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
		0.f,  0.f,  0.f, // 0
		0.f,  0.f,  1.f, // 1
		0.f,  1.f,  0.f, // 2
		0.f,  1.f,  1.f, // 3 
	
		1.f,  0.f,  0.f, // 4
		1.f,  0.f,  1.f, // 5
		1.f,  1.f,  0.f, // 6
		1.f,  1.f,  1.f, // 7
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

	m_Buffer = new VertexBuffer(vertices, 8 * 4 * sizeof(float));
	m_Buffer->Bind();

	m_Layout = new VertexBufferLayout({
			{GL_FLOAT, 3, GL_FALSE}
	});

	m_IndexBuffer = new IndexBuffer(indices, 6 * 6);

	m_Vao->AddBuffer(*m_Buffer, *m_Layout);

	m_BlueTriangle = new Shader("res/shaders/shader.glsl");
	m_BlueTriangle->Use();
	
	m_Projection = glm::mat4(glm::perspective(45.f, 640.f/480.f, 0.1f, 150.f));
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

static int framecount = 0;

static void worker(std::atomic<int>* num)
{
	(*num)++;
	spdlog::error(*num);
}

static float rChannel = 0.f;
static float delta = 0.001f;

void Layer3D::OnUpdate(float timestep)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	UpdatePositions(timestep);
	
	m_BlueTriangle->Use();
	m_Vao->Bind();
	m_IndexBuffer->Bind();
	
	// test to see how data sharing works across threads
	std::atomic<int> num = 10;
	num++;
	std::thread t(worker, &num);
	t.join();
	spdlog::info(num);
	// ------------------
	
	glm::mat4 translation = glm::translate(glm::mat4(1.f), m_Pos);
	glm::mat4 rotation = glm::rotate(m_Angle.y, glm::vec3(1.f, 0.f, 0.f));
	rotation = glm::rotate(rotation, m_Angle.x, glm::vec3(0.f, 1.f, 0.f));
	
	m_BlueTriangle->UploadUniformMat4("u_Projection", m_Projection);
	m_BlueTriangle->UploadUniformMat4("u_Translation", translation);
	m_BlueTriangle->UploadUniformMat4("u_Rotation", rotation);
	
	rChannel += delta;
	if (rChannel > 1.f || rChannel < 0.f) delta = -delta;

	m_BlueTriangle->UploadUniformf("u_rChannel", rChannel);

//	std::thread t(worker, m_BlueTriangle, std::ref(m_Pos), std::ref(m_Angle), std::ref(m_Projection));
//	t.join();
	for (int i = 0; i < 20; i+=2) {
//		std::thread t(worker, i, m_BlueTriangle);
//		t.join();
		for (int j = 0; j < 20; j+=2)
			for (int k = 0; k < 20; k+=2)
			{
				glm::mat4 position = glm::translate(glm::mat4(1.f), glm::vec3((float)i, (float)k, (float)j));
				m_BlueTriangle->UploadUniformMat4("u_Position", position);
				GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr)); // 6 sides * two triangles per side
			}
	}
	
	framecount++;
	if (framecount == 10000) {
		spdlog::info("fps: {}", 1.f/timestep);
		framecount = 0;
	}
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
		
		// make sure the camera cannot flip backwards
		m_Angle.y = std::clamp(m_Angle.y, -glm::pi<float>() / 2, glm::pi<float>() / 2);
		m_PrevMousePos = currentPos;
	}
	
	if (e.GetEventType() == EventType::KeyPressed) {
		KeyPressedEvent& kpe = (KeyPressedEvent&)e;		
		m_KeyDown[kpe.GetKeyCode()] = true;
	}
	
	if (e.GetEventType() == EventType::KeyReleased) {
		KeyReleasedEvent& kre = (KeyReleasedEvent&)e;
		m_KeyDown[kre.GetKeyCode()] = false;
	}
	
	UpdateDirection(GLFW_KEY_A, GLFW_KEY_D, m_Mov.LR);
	UpdateDirection(GLFW_KEY_S, GLFW_KEY_W, m_Mov.FB);
	UpdateDirection(GLFW_KEY_LEFT_SHIFT, GLFW_KEY_SPACE, m_Mov.UD);
}


void Layer3D::UpdatePositions(float timestep) {
	m_Pos.x += timestep * m_Mov.LR * m_MovSpeed * glm::cos(m_Angle.x);
	m_Pos.z += timestep * m_Mov.LR * m_MovSpeed * glm::sin(m_Angle.x);

	m_Pos.y += timestep * m_Mov.UD * m_MovSpeed;

	m_Pos.z -= timestep * m_Mov.FB * m_MovSpeed * glm::cos(m_Angle.x);
	m_Pos.x += timestep * m_Mov.FB * m_MovSpeed * glm::sin(m_Angle.x);
}


void Layer3D::UpdateDirection(int negative_dir_key, int positive_dir_key, int& axis)
{
	if (m_KeyDown[negative_dir_key])
		if (m_KeyDown[positive_dir_key])
			axis = 0;
		else
			axis = 1;
	else if (m_KeyDown[positive_dir_key])
		axis = -1;
	else
		axis = 0;
}