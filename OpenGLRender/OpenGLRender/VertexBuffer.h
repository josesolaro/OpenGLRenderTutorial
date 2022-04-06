#pragma once
#include "GL/glew.h"

class VertexBuffer {
public:
	VertexBuffer(void* data, unsigned long size);
	~VertexBuffer();
	void SetLayout(int layoutPosition, int dataPerVertex, int stride,  int offset);
	void Bind();
	void Unbind();
private:
	unsigned int m_VertexBufferId;
};