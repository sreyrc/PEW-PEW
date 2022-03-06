#include <glad/glad.h>

#include "Shader.h"


std::string Shader::GetFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);

}

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile)
	:	mShaderProgramID(0)
{
	std::string vertexShaderCode = GetFileContents(vertexShaderFile);
	std::string fragmentShaderCode = GetFileContents(fragmentShaderFile);

	const char* vertexShaderSource = vertexShaderCode.c_str();
	const char* fragmentShaderSource = fragmentShaderCode.c_str();

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShaderID);

	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShaderID);

	mShaderProgramID = glCreateProgram();

	glAttachShader(mShaderProgramID, vertexShaderID);
	glAttachShader(mShaderProgramID, fragmentShaderID);
	glLinkProgram(mShaderProgramID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::UseProgram()
{
	glUseProgram(mShaderProgramID);
}

void Shader::SetMat4(glm::mat4 matrix, std::string name)
{
	GLuint loc = glGetUniformLocation(mShaderProgramID, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVec3(glm::vec3 vector3, std::string name)
{
	GLuint loc = glGetUniformLocation(mShaderProgramID, name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(vector3));
}

void Shader::Set1i(int i, std::string name)
{
	GLuint loc = glGetUniformLocation(mShaderProgramID, name.c_str());
	glUniform1i(loc, i);
}

Shader::~Shader()
{
	glDeleteProgram(mShaderProgramID);
}
