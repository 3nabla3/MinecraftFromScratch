#pragma once
#include "Layer.h"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/VertexBufferLayout.h"
#include "OpenGL/Shader.h"

class Layer3D : public Layer
{
public:
	Layer3D(const std::string& name);
	~Layer3D();
	
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate(float timestep);
	virtual void OnEvent(Event& e);
	
	void UpdatePositions(float timestep);
private:
	std::string m_DebugName;

	VertexArray* m_Vao = nullptr;
	VertexBuffer* m_Buffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexBufferLayout* m_Layout = nullptr;
	Shader* m_BlueTriangle = nullptr;
	
	glm::mat4 m_Projection;
	glm::vec3 m_Pos = glm::vec3(-0.5f, -0.5f, -2.0f);
	glm::vec2 m_Angle = glm::vec2(0.f, 0.f);
	glm::vec2 m_PrevMousePos = glm::vec2(-1.f, -1.f);
	
	struct {
		int LR = 0;
		int UD = 0;
		int FB = 0;
	} m_Mov;
	
	float m_MovSpeed = 5.f;
	float m_AngleSpeed = 0.01f;
};
