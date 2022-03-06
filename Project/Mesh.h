#pragma once

#include <glad/glad.h>
#include "GameObject.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void CreateMeshes();

public:
	GLuint mVAO, mVBO, mEBO;

private:

	GLfloat mVertices[32] =
	{
		  // positions			//tex color			// tex coords
		  1.0f, -1.0f, 0.0f,	1.0f, 0.5f, 1.0f,	1.0f,  0.0f, 
		  1.0f,  1.0f, 0.0f,	1.0f, 1.0f, 0.5f,	1.0f,  1.0f,
		 -1.0f,  1.0f, 0.0f,    0.5f, 1.0f, 1.0f,	0.0f,  1.0f,
		 -1.0f, -1.0f, 0.0f,    1.0f, 1.0f, 1.0f,	0.0f,  0.0f
	};

	GLuint mIndices[6] = { 0, 1, 2, 2, 3, 0 };

};

