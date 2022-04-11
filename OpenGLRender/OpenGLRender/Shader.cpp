#include "GL/glew.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include "shader.h"

namespace renderer {

	ShaderProgram::ShaderProgram(const char* filesPath)
	{
		ShaderProgramSource source = LoadShaderSource(filesPath);
		unsigned int vertexShaderId = CompileShader(GL_VERTEX_SHADER, &source.VertexSource);
		unsigned int fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, &source.FragmentSource);

		//linking shaders together.
		unsigned int programId = glCreateProgram();
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);
		glLinkProgram(programId);

		int status;
		glGetProgramiv(programId, GL_LINK_STATUS, &status);
		if (!status) {
			int length;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetProgramInfoLog(programId, length, &length, message);
			std::cout << "Fail linking program" << std::endl;
			std::cout << message << std::endl;
			glDeleteProgram(programId);
		}

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
		m_ProgramId = programId;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ProgramId);
	}

	void ShaderProgram::Bind()
	{
		glUseProgram(m_ProgramId);
	}

	void ShaderProgram::Unbind()
	{
		glUseProgram(0);
	}

	void ShaderProgram::SetUniform4f(const char* uniformName, float* vec4)
	{
		uint32_t id = glGetUniformLocation(m_ProgramId, uniformName);
		glUniform4fv(id, 1, vec4);
	}
	void ShaderProgram::SetUniformMatrix4f(const char* uniform, float* mat4) {
		uint32_t id = glGetUniformLocation(m_ProgramId, uniform);
		glUniformMatrix4fv(id, 1, GL_FALSE, mat4);
	}

	void ShaderProgram::SetUniform1f(const char* uniformName, float value) {
		uint32_t id = glGetUniformLocation(m_ProgramId, uniformName);
		glUniform1f(id, value);
	}

	void ShaderProgram::SetUniform1i(const char* uniformName, int value) {
		uint32_t id = glGetUniformLocation(m_ProgramId, uniformName);
		glUniform1i(id, value);
	}

	ShaderProgramSource ShaderProgram::LoadShaderSource(const char* filePath) {
		enum class ShaderType {
			NONE = 0,
			VERTEX = 1,
			FRAGMENT = 2
		};
		ShaderType type = ShaderType::NONE;
		const char* vertexHeader = "#!VERTEX";
		const char* fragmentHeader = "#!FRAGMENT";
		std::string vertexShaderCode;
		std::string fragmentShaderCode;
		std::ifstream shaderFile(filePath);

		if (shaderFile.is_open()) {
			std::string line;
			while (getline(shaderFile, line)) {
				if (line.empty()) {
					continue;
				}
				if (line.compare(vertexHeader) == 0) {
					type = ShaderType::VERTEX;
					continue;
				}
				else if (line.compare(fragmentHeader) == 0) {
					type = ShaderType::FRAGMENT;
					continue;
				}
				line = line.append("\n");
				switch (type) {
				case ShaderType::VERTEX: {
					vertexShaderCode.append(line);
					break;
				}
				case ShaderType::FRAGMENT: {
					fragmentShaderCode.append(line);
					break;
				}
				default:
					continue;
				}
			}
		}
		shaderFile.close();
		return { vertexShaderCode, fragmentShaderCode };
	}

	unsigned int ShaderProgram::CompileShader(unsigned int type, std::string* source) {
		unsigned int id = glCreateShader(type);
		const char* src = source->c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);
		int status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if (!status) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Fail " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "shader compilation" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			return 0;
		}
		return id;
	}
}