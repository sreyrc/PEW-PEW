#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
out vec2 TexCoord;
out vec4 color;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
void main()
{
	gl_Position = projectionMatrix * modelMatrix * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
	color = vec4(aColor, 1.0);
}