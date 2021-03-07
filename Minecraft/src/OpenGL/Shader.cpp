#include "pch.h"

#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

struct Shader::ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};


Shader::ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];
	std::string line;
	while (getline(stream, line))
	{
		if (line.find("#shader vertex") != std::string::npos)
			type = ShaderType::VERTEX;
		else if (line.find("#shader fragment") != std::string::npos)
			type = ShaderType::FRAGMENT;

		else if (type != ShaderType::NONE)
			ss[(int)type] << line << std::endl;
	}

	return { ss[0].str() , ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int shader = glCreateShader(type));
	const char* str = source.c_str();
	GLCall(glShaderSource(shader, 1, &str, NULL));
	GLCall(glCompileShader(shader));
	int result;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	if (!result)
	{
		int length;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)malloc(length);
		GLCall(glGetShaderInfoLog(shader, length, &length, message));
		spdlog::error("Failed to compile {} shader\n", (type == GL_VERTEX_SHADER ? "vertex" : "framgent"));
		spdlog::error(message);
	}

	return shader;
}

unsigned int Shader::CreateProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	unsigned int program;
	GLCall(program = glCreateProgram());
	GLCall(glAttachShader(program, fs));
	GLCall(glAttachShader(program, vs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	return program;
}

Shader::Shader(const std::string& filepath)
	:m_Filepath(filepath), m_Id(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_Id = CreateProgram(source.VertexShader, source.FragmentShader);
}

Shader::~Shader()
{
}

void Shader::Use() const
{
	GLCall(glUseProgram(m_Id));
}

void Shader::Unuse() const
{
	GLCall(glUseProgram(0));
}

void Shader::UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix) const
{
	int location = GetUniformLocation(uniformName);

	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)));
}

unsigned int Shader::GetUniformLocation(const std::string& uniformName) const
{
	GLCall(int location = glGetUniformLocation(m_Id, uniformName.c_str()));
	if (location == -1)
		spdlog::warn("Uniform {} does not exist!", uniformName);

	return location;
}
