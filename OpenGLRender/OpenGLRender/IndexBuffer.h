#pragma once

class IndexBuffer {
public:
	IndexBuffer(void* indices, unsigned long size);
	~IndexBuffer();
	void Bind();
	void Unbind();
private:
	unsigned int m_IndexBufferId;
};