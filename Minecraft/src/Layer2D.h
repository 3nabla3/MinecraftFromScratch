#include "Layer.h"

#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Shader.h"

class Layer2D : public Layer
{
public:
	Layer2D(const std::string& name);
	~Layer2D();
	
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnEvent(Event& e);
	virtual void OnUpdate(float timestep);
private:
	VertexArray* m_VertexArray;
	VertexBuffer* m_VertexBuffer = nullptr;
	IndexBuffer* m_IndexBuffer = nullptr;
	VertexBufferLayout* m_Layout = nullptr;
	
	Shader* m_Shader = nullptr;
};