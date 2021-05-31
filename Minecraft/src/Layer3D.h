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

	virtual bool OnKeyPressed(KeyPressedEvent& e);
	virtual bool OnKeyReleased(KeyReleasedEvent& e);
	virtual bool OnMouseMoved(MouseMovedEvent& e);
	virtual bool OnWindowResize(WindowResizeEvent& e);
	
private:
	void UpdatePositions(float timestep);
	void UpdateDirection(int negative_dir_key, int positive_dir_key, int& axis);

	VertexArray* m_Vao = nullptr;
	VertexBuffer* m_Buffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexBufferLayout* m_Layout = nullptr;
	Shader* m_BlueTriangle = nullptr;
	
	glm::mat4 m_Projection;
	glm::vec3 m_Pos = glm::vec3(-0.5f, -0.5f, -2.0f);
	glm::vec2 m_Angle = glm::vec2(0.f, 0.f);
	glm::vec2 m_PrevMousePos = glm::vec2(-1.f, -1.f);
	
	// stores whether a key is pressed down
	std::unordered_map<int, bool> m_KeyDown = {
		{GLFW_KEY_A, false},
		{GLFW_KEY_D, false},
		
		{GLFW_KEY_W, false},
		{GLFW_KEY_S, false},
		
		{GLFW_KEY_LEFT_SHIFT, false},
		{GLFW_KEY_SPACE, false},

		{GLFW_KEY_LEFT_CONTROL, false},
		
		{GLFW_KEY_LEFT_BRACKET, false},
		{GLFW_KEY_RIGHT_BRACKET, false}
	};
	
	struct {
		// left-right / up-down / forward-backward
		int LR = 0;
		int UD = 0;
		int FB = 0;
	} m_Mov;
	
	float m_AngleSpeed = 0.001f;

	float m_NormalMovSpeed = 5.f;
	float m_SprintingMovSpeed = 15.f;
	float m_MovSpeed = m_NormalMovSpeed;
	
	float m_FOV = 90.f;
};
