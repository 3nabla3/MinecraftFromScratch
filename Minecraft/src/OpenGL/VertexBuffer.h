#pragma once
#include "VertexBufferLayout.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	/*void SetLayout(VertexBufferLayout* layout) { m_Layout = layout; }
	const VertexBufferLayout* GetLayout() { return m_Layout; }*/

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_Id;
	const void* m_Data;
};

