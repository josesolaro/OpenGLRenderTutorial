#include "renderer.h"
#include <iostream>
#include "shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

namespace renderer {

	void render(float elapsedTime, float mixTexture) {

		ShaderProgram program = ShaderProgram("shaders/uni.shader");

		stbi_set_flip_vertically_on_load(true);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		////pack some buffers together
		VertexArray vertexArray = VertexArray();
		vertexArray.Bind();

		VertexBuffer vertexBuffer = VertexBuffer((void*)vertices, sizeof(vertices));
		vertexBuffer.SetLayout(0, 3, 8 * sizeof(float), 0 * sizeof(float));//pos
		vertexBuffer.SetLayout(1, 3, 8 * sizeof(float), 3 * sizeof(float));//color
		vertexBuffer.SetLayout(2, 2, 8 * sizeof(float), 6 * sizeof(float));//tex

		IndexBuffer indexBuffer = IndexBuffer((void*)indices, 6 * sizeof(float));

		
		int width, height, nrChannels;
		unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
		Texture tex1 = Texture(0, width, height, data, ImageFormat::JPG);
		stbi_image_free(data);


		data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
		Texture tex2 = Texture(1, width, height, data, ImageFormat::PNG);
		stbi_image_free(data);


		program.Bind();
		program.SetUniform1i("boxTexture", 0);
		program.SetUniform1i("faceTexture", 1);
		program.SetUniform1f("texMix", mixTexture);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



	}
}