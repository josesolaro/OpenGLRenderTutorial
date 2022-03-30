#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_VertexArrayId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_VertexArrayId);
}

void VertexArray::Bind()
{
	glBindVertexArray(m_VertexArrayId);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
