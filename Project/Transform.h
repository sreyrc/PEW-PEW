#pragma once

#include "Component.h"
#include <glm/glm.hpp>

class Transform : public Component {

public:
	Transform() { mPos = glm::vec2(0.0f); mScale = glm::vec2(0.0f); mRotation = 0.0f; };
	~Transform() {};
	void Update();
	void Deserialize(rapidjson::GenericObject<false, rapidjson::Value::ValueType> transformObj);
	void HandleEvent(Event* pEvent);

public:
	glm::vec2 mPos;
	glm::vec2 mScale;
	float mRotation;
};