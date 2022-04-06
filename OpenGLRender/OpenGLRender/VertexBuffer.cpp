#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, unsigned long size)
{
	glGenBuffers(1, &m_VertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	//load data in vram (relative slow)
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VertexBufferId);
}

void VertexBuffer::SetLayout(int layoutPosition,int dataPerVertex, int stride, int offset)
{
	//how to read that data
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferId);
	glVertexAttribPointer(layoutPosition, dataPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(layoutPosition);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_VERTEX_ARRAY, m_VertexBufferId);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}
