#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, unsigned long size, int dataPerVertex, int layoutPosition)
{
	glGenBuffers(1, &m_VertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	//load data in vram (relative slow)
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	//how to read that data
	glVertexAttribPointer(layoutPosition, dataPerVertex, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(layoutPosition);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VertexBufferId);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_VERTEX_ARRAY, m_VertexBufferId);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}
