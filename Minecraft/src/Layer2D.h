#pragma once
#include "Layer.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexBufferLayout.h"
#include "OpenGL/Shader.h"

class Layer2D : public Layer
{
public:
	Layer2D(const std::string& name);
	~Layer2D();
	
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(float timestep);
	virtual void OnEvent(Event& e);
private:
	std::string m_DebugName;

	VertexArray* m_Vao = nullptr;
	VertexBuffer* m_Buffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexBufferLayout* m_Layout = nullptr;
	Shader* m_BlueTriangle = nullptr;
	
	glm::mat4* m_Camera = nullptr;
	
	float m_xPos = -0.5f , m_yPos = -0.5f, m_zPos = -2.0f;
	float m_Angle = 0.0f;
};