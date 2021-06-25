#include "pch.h"

#include "VertexArray.h"

VertexArray::VertexArray()
	:m_Id(0)
{
	GLCall(glCreateVertexArrays(1, &m_Id));
}

VertexArray::~VertexArray()
{
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_Id));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	uint64_t offset = 0; // has to be a 64 bit integer to avoid warning when converted to a pointer
	for (int i = 0; i < elements.size(); i++)
	{
		const auto& e = elements.at(i);
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (const void*)offset));
		offset += (uint64_t)e.count * e.GetSize();
	}
}
