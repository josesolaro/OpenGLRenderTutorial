#pragma once

namespace renderer {
	struct ShaderProgramSource {
		std::string VertexSource;
		std::string FragmentSource;
	};

	class ShaderProgram {
	public:
		ShaderProgram(const char* filesPath);
		~ShaderProgram();
		void Bind();
		void Unbind();
		void SetUniform4f(const char* uniformName, float* vec4);
		void SetUniform1f(const char* uniformName, float value);
		void SetUniform1i(const char* uniformName, int value);
		void SetUniformMatrix4f(const char* uniform, float* mat4);
		inline unsigned int ProgramId() { return m_ProgramId; }
	private:
		unsigned int m_ProgramId;
		ShaderProgramSource LoadShaderSource(const char* filePath);
		unsigned int CompileShader(unsigned int type, std::string* source);
	};
}
