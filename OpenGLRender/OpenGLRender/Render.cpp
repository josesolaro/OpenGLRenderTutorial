#include "renderer.h"
#include <iostream>
#include "shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace renderer {

	void render(float elapsedTime) {

		ShaderProgram program = ShaderProgram("shaders/uni.shader");
		
		float vertices[] = {
			-0.5f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f, 
			 0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
			 0.0f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
		};

		////pack some buffers together
		VertexArray vertexArray = VertexArray();
		vertexArray.Bind();

		VertexBuffer vertexBufferPos = VertexBuffer((void*)vertices, sizeof(vertices), 3, 0, 0, 6 * sizeof(float));
		VertexBuffer vertexBufferColor = VertexBuffer((void*)vertices, sizeof(vertices), 3, 1, 3 * sizeof(float), 6 * sizeof(float));

		program.Bind();

		program.SetUniform1f("hOffset", -0.5f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		vertexBufferPos.Unbind();
		vertexBufferColor.Unbind();
		program.Unbind();

	}
}