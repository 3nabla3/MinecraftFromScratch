#pragma once
#include "VertexBufferLayout.h"

class VertexBuffer
{
public:
	VertexBuffer(float* vertices, unsigned int size);
	~VertexBuffer();

	void SetLayout(VertexBufferLayout* layout) { m_Layout = layout; }

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_Id;
	float* m_Vertices;

	VertexBufferLayout* m_Layout;
};

