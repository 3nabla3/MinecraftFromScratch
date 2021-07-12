#include "pch.h"

#include "Layer2D.h"
#include "SOIL/SOIL.h"
#include "glm/gtc/matrix_transform.hpp"

static unsigned int textureID;

Layer2D::Layer2D(const std::string& name)
	:Layer(name)
{
	spdlog::trace("Layer {} was created", m_DebugName);
	
	
	float vertices[] = {
	//  Position  Color             Texcoords
    -0.5f,  0.5f,// 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f,// 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
    -0.5f, -0.5f,// 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	 0.5f, -0.5f,// 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
	};
	
	unsigned int indices[] = {
		0, 1, 2, 1, 2, 3
	};
	
	m_VertexArray = new VertexArray();
	
	m_VertexBuffer = new VertexBuffer(vertices, 2 * 6 * sizeof(float));
	m_VertexBuffer->Bind();
	
	m_Layout = new VertexBufferLayout({
		{GL_FLOAT, 2, GL_FALSE}, // position
//		{GL_FLOAT, 3, GL_FALSE}, // color
//		{GL_FLOAT, 2, GL_FALSE}  // tex coords
	});
	
	m_IndexBuffer = new IndexBuffer(indices, 6);
	m_VertexArray->AddBuffer(*m_VertexBuffer, *m_Layout);
	
	m_Shader = new Shader("res/shaders/simpleShader.glsl");
	m_Shader->Use();

//	int x, y, c;
//	unsigned char* data = SOIL_load_image("res/textures/wood.jpeg", &x, &y, &c, SOIL_LOAD_RGB);
//	spdlog::info("Loaded image of size {} by {}", x, y);
//
//	
//	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
//	glTextureStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, x, y);
//	
//	glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	
//	glTextureSubImage2D(textureID, 0, 0, 0, x, y, GL_RGBA, GL_UNSIGNED_BYTE, data);
//	SOIL_free_image_data(data);
}

void Layer2D::OnAttach()
{
	spdlog::trace("Layer {} was attached", m_DebugName);
}

void Layer2D::OnDetach()
{
	spdlog::trace("Layer {} was detached", m_DebugName);
}

void Layer2D::OnEvent(Event& e)
{
	
}

void Layer2D::OnUpdate(float timestep)
{
	// Only clear the depth buffer to make sure the 2D layer is always on top
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
	
	m_Shader->Use();
	m_VertexArray->Bind();
	m_IndexBuffer->Bind();
//	glm::mat4 proj = glm::ortho(-10.f, 10.f, -10.f, 10.f, 1.f, 150.f);
//	m_Shader->UploadUniformMat4("u_Projection", proj);
//	m_Shader->UploadUniformMat4("u_Translation", glm::mat4(1.0f));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}