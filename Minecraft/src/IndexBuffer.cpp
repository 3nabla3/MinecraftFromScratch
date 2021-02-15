#include "IndexBuffer.h"
#include "Core.h"

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int count)
	:m_Indices(indices), m_Count(count)
{
	GLCall(glGenBuffers(1, &m_Id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_Id));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}