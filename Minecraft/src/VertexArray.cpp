#include "VertexArray.h"
#include "Core.h"

VertexArray::VertexArray()
	:m_Id(0)
{
	GLCall(glGenVertexArrays(1, &m_Id));
	GLCall(glBindVertexArray(m_Id));
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
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		const auto& e = elements.at(i);
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.GetStride(), (const void*)offset));
		offset += e.count * e.GetSize();
	}
}
