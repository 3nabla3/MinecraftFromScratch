#pragma once
#include <fstream>

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Use() const;
	void Unuse() const;

	void UploadUniformMat4(const std::string& uniformName, const glm::mat4& matrix) const;
	void UploadUniformf(const std::string& uniformName, float value) const;
	void UploadUniformi(const std::string& uniformName, int value) const;

private:
	unsigned int m_Id;
	const std::string& m_Filepath;

	struct ShaderProgramSource;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateProgram(const std::string& vertexSource, const std::string& fragmentSource);
	unsigned int GetUniformLocation(const std::string& uniformName) const;
};

