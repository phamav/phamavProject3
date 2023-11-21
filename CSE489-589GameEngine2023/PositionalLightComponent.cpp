#include "PositionalLightComponent.h"

PositionalLightComponent::PositionalLightComponent(int controlkey)
	: LightComponent(controlkey) {}

void PositionalLightComponent::update(const float& deltaTime) {
	// update the light's positions
	// based on its GameObject's world position
	if (owningGameObject) {
		glm::vec3 worldPos = owningGameObject->getPosition();
		glm::vec4 lightPos = glm::vec4(worldPos, 1.0f);
		setPositionOrDirection(lightPos);
	}
}