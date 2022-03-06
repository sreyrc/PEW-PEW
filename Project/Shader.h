#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{

public:
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
	~Shader();
	std::string GetFileContents(const char* filename);
	void UseProgram();
	GLuint GetProgramID() { return mShaderProgramID; }

	void SetMat4(glm::mat4, std::string);
	void SetVec3(glm::vec3, std::string);
	void Set1i(int i, std::string);

private:
	GLuint mShaderProgramID;
};

