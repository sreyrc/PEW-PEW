#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <map>

class Renderer
{
public:
	Renderer();
	~Renderer() {};

	void IntializeColorMap();

	void Draw();
	void Clear();
	void BuildTransforms(GameObject* gameObject);
	void SetShaderVariables(GameObject* gameObject);
	void ToggleDebugMode();

private:
	std::unordered_map<std::string, glm::vec3> mColorVal;
	glm::mat4 projectionMatrix, modelMatrix;
	int mRenderMode;
};
