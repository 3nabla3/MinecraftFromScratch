#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* indices, unsigned int count);
	~IndexBuffer();

	unsigned int GetCount() const { return m_Count; }

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_Id;
	const unsigned int* m_Indices;
	unsigned int m_Count;
};

