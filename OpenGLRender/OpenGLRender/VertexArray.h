#pragma once
#include "GL/glew.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
private:
	unsigned int m_VertexArrayId;
};