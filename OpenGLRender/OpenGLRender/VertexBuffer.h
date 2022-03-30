#pragma once
#include "GL/glew.h"

class VertexBuffer {
public:
	VertexBuffer(void* data, unsigned long size, int dataPerVertex, int layoutPosition);
	~VertexBuffer();
	void Bind();
	void Unbind();
private:
	unsigned int m_VertexBufferId;
};