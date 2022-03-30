#include "GL/glew.h"
#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(void* indices, unsigned long size)
{
	glGenBuffers(1, &m_IndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_IndexBufferId);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferId);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
