#pragma once
#include "Component.h"

class ArrowRotateComponent : public Component
{
public:

	ArrowRotateComponent(float rotRateDegreesPerSec = 30.0f, int updateOrder = 150);

	virtual void update(const float& deltaTime) override;

	virtual void processInput();

protected:

	/** @brief	The rotation rate in radians per second */
	float radianRotRate;

	mat4 matRotIncrement;
	float speed = 10.0f;
	vec3 destination = vec3(10.0f, 0.0f, 70.0f);
};


