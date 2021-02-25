#pragma once
#include <utility>
#include <vector>
#include "Core.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	unsigned int GetSize() const
	{
		switch (type)
		{
		case GL_SHORT:
			return sizeof(short);
		case GL_UNSIGNED_SHORT:
			return sizeof(unsigned short);
		case GL_INT:
			return sizeof(int);
		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);
		case GL_FLOAT:
			return sizeof(float);
		case GL_DOUBLE:
			return sizeof(double);
		default:
			spdlog::error("Type does not exist");
			return 0;
			break;
		}
	}
};

class VertexBufferLayout
{
public:

	VertexBufferLayout(std::vector<VertexBufferElement> elements)
		: m_Elements(elements), m_Stride(0)
	{
		for (int i = 0; i < elements.size(); i++)
			m_Stride += elements[i].count * elements[i].GetSize();
	}

	std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	unsigned int GetStride() const { return m_Stride; }

private:
	unsigned int m_Stride;

	std::vector<VertexBufferElement> m_Elements;
};

