#pragma once
class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(float* vertices, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
private:
	unsigned int m_Id;
	float* m_Vertices;
};

