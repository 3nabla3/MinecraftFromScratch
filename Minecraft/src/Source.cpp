#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <fstream>
#include <sstream>

#define ASSERT(x) if (!x) std::cout << "Error!!!" << std::endl;
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const std::string& signature, const std::string& filename, int linenumber)
{
	if (GLenum error = glGetError())
		std::cout << "[OpenGL Error] (" << error << ") " << signature << ": " << filename << "(" << linenumber << ")" << std::endl; return true;
	return false;
}

struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
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

static unsigned int CompileShader(unsigned int type, const std::string& source)
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
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "framgent") << " shader" << std::endl;
		std::cout << message << std::endl;
	}

	return shader;
}

static unsigned int CreateProgram(const std::string& vertexSource, const std::string& fragmentSource)
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

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "Failed to initialize Glad" << std::endl;

	float vertices[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f, 
		 0.5f, -0.5f
	};

	unsigned int buffer;
	GLCall(glGenBuffers(1, &buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

	ShaderProgramSource source = ParseShader("res/shaders/shader.glsl");
	unsigned int program = CreateProgram(source.VertexShader, source.FragmentShader);
	glUseProgram(program);

	while (!glfwWindowShouldClose(window))
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}