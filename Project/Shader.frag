#version 330 core
uniform vec3 myColor;
uniform sampler2D myTexture;
uniform int mode;
in vec4 color;
in vec2 TexCoord;
out vec4 FragColor;
void main()
{
	if (mode == 0) {
		FragColor = texture(myTexture, TexCoord);
	}
	if (mode == 1) {
		FragColor = color * vec4(myColor, 1.0f);
	}
}