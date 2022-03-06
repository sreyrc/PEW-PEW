#include <glad/glad.h>
#include <gl/GL.h>

#include "GameObjectManager.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "WorldVariables.h"

#include "Transform.h"
#include "Sprite.h"

extern GameObjectManager* gpGameObjectManager;
extern Mesh* gpMesh;
extern Shader* gpShader;

Renderer::Renderer()
{
	projectionMatrix = glm::ortho(0.0f, 400.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	modelMatrix = glm::mat4(1.0f);

	IntializeColorMap();
};


void Renderer::IntializeColorMap()
{
	mColorVal["Purple"] = glm::vec3(0.5f, 0.0f, 0.5f);
	mColorVal["Yellow"] = glm::vec3(1.0f, 1.0f, 0.0f);
	mColorVal["Green"] = glm::vec3(0.0f, 1.0f, 0.0f);
	mColorVal["Red"] = glm::vec3(1.0f, 0.0f, 0.0f);
	mColorVal["Cyan"] = glm::vec3(0.0f, 1.0f, 1.0f);
}


void Renderer::Draw()
{
	std::vector<GameObject*>* gameObjectList = gpGameObjectManager->GetGameObjectList();

	for (auto i : *gameObjectList) {

		if (i->GetComponent<Sprite>() != nullptr) {

			glBindVertexArray(gpMesh->mVAO);
			BuildTransforms(i);
			gpShader->UseProgram();
			i->GetComponent<Sprite>()->mpTexture->Bind(gpShader->GetProgramID(), "myTexture");
			SetShaderVariables(i);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
}


void Renderer::Clear()
{
	glClearColor(0.12f, 0.12f, 0.12f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::BuildTransforms(GameObject* gameObject)
{
	Transform* transform = gameObject->GetComponent<Transform>();

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(transform->mPos, 0.0f));

	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f * (transform->mScale).x, 0.5f * (transform->mScale).y, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform->mRotation), glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f * (transform->mScale).x, -0.5f * (transform->mScale).y, 0.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(transform->mScale, 1.0f));
}


void Renderer::SetShaderVariables(GameObject* gameObject)
{
	gpShader->SetMat4(modelMatrix, "modelMatrix");
	gpShader->SetMat4(projectionMatrix, "projectionMatrix");
	gpShader->SetVec3(mColorVal[gameObject->mColor], "myColor");
	gpShader->Set1i(mRenderMode, "mode");
}

void Renderer::ToggleDebugMode()
{
	mRenderMode = !mRenderMode;

	if (mRenderMode == 1) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
