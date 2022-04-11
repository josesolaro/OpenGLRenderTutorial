#include "renderer.h"
#include <iostream>
#include "shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "vendor/stb_image/stb_image.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

namespace renderer {

	void render(float wWidth, float wHeight, float elapsedTime, float mixTexture) {

		ShaderProgram program = ShaderProgram("shaders/uni.shader");

		stbi_set_flip_vertically_on_load(true);

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};
		
		////pack some buffers together
		VertexArray vertexArray = VertexArray();
		vertexArray.Bind();

		VertexBuffer vertexBuffer = VertexBuffer((void*)vertices, sizeof(vertices));
		vertexBuffer.SetLayout(0, 3, 5 * sizeof(float), 0 * sizeof(float));//pos
		vertexBuffer.SetLayout(2, 2, 5 * sizeof(float), 3 * sizeof(float));//tex


		int width, height, nrChannels;
		unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
		Texture tex1 = Texture(0, width, height, data, ImageFormat::JPG);
		stbi_image_free(data);


		data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
		Texture tex2 = Texture(1, width, height, data, ImageFormat::PNG);
		stbi_image_free(data);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
		model = glm::rotate(model, elapsedTime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), wWidth / wHeight, 0.1f, 100.f);


		program.Bind();
		program.SetUniformMatrix4f("model", (float*)&model);
		program.SetUniformMatrix4f("view", (float*)&view);
		program.SetUniformMatrix4f("proj", (float*)&proj);

		program.SetUniform1i("boxTexture", 0);
		program.SetUniform1i("faceTexture", 1);
		program.SetUniform1f("texMix", mixTexture);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -5.0f));
		program.SetUniformMatrix4f("model", (float*)&model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
}