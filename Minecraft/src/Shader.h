#pragma once
#include <fstream>

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Use();
	void Unuse();

private:
	unsigned int m_Id;
	const std::string& m_Filepath;

	struct ShaderProgramSource;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateProgram(const std::string& vertexSource, const std::string& fragmentSource);
};

