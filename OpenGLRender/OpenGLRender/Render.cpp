#include "renderer.h"
#include <iostream>
#include "shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace renderer {

	void render() {

		ShaderProgram program = ShaderProgram("shaders/uni.shader");

		
		int dataPerVertex = 3;
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		////pack some buffers together
		VertexArray vertexArray = VertexArray();
		vertexArray.Bind();
		
		VertexBuffer vertexBuffer = VertexBuffer((void*)vertices, sizeof(vertices), dataPerVertex, 0);
		IndexBuffer indexBuffer = IndexBuffer(indices, sizeof(indices));
		
		////VAO stores unbind of glBindBUffer(index) so first unbind vertexarray
		vertexArray.Unbind();
		indexBuffer.Unbind();

		program.Bind();

		
		vertexArray.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}
}